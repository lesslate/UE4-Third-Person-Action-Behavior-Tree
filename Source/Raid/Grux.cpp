// Fill out your copyright notice in the Description page of Project Settings.

#include "Grux.h"
#include "Sound/SoundCue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "GruxAIController.h"
#include "GruxAnimInstance.h"
#include "RaidGameMode.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AGrux::AGrux()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 500;
	GruxMaxHP = 1000000;
	GruxHP = GruxMaxHP;

	AIControllerClass = AGruxAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	// 스켈레탈 메시 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GRUXMESH(TEXT("SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Skins/Tier_2/Grux_Beetle_Molten/Meshes/GruxMolten.GruxMolten'"));
	if (GRUXMESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(GRUXMESH.Object);
	}

	// 애니메이션 블루프린트 속성지정
	static ConstructorHelpers::FClassFinder<UAnimInstance> GRUXANIM(TEXT("AnimBlueprint'/Game/Characters/BP_GruxAnim.BP_GruxAnim_C'")); // _C를 붙여 클래스정보를 가져옴
	if (GRUXANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(GRUXANIM.Class);
	}
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(GetMesh());

	// 오디오 컴포넌트 초기화
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GruxAudio"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(GetMesh());

	// 캡슐 컬리전 생성
	GruxLeftCheck = CreateDefaultSubobject<UCapsuleComponent>(TEXT("GruxLeftCheck"));
	GruxLeftCheck->SetupAttachment(GetMesh(), TEXT("FX_Trail_L_02"));
	GruxRightCheck = CreateDefaultSubobject<UCapsuleComponent>(TEXT("GruxRightCheck"));
	GruxRightCheck->SetupAttachment(GetMesh(), TEXT("FX_Trail_R_02"));

	GruxLeftCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GruxRightCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AGrux::BeginPlay()
{
	Super::BeginPlay();
	
	if (GruxAI!=nullptr)
	{
		GruxAI->StopAI();
		GruxAnim->PlayStartMontage();
		GetWorld()->GetTimerManager().SetTimer(timer, this, &AGrux::AIStart, 5.2f, false); // 시작 몽타주 재생후 패턴시작
	}
}

/////////////// Apply damage////////////

void AGrux::ServerApplyDamage_Implementation(AActor * DamagedActor, float Damamge, AActor * DamageCauser)
{
	UGameplayStatics::ApplyDamage(DamagedActor, Damage, nullptr, DamageCauser, nullptr);
	GruxLeftCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GruxRightCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AGrux::ServerApplyDamage_Validate(AActor * DamagedActor, float Damamge, AActor * DamageCauser)
{
	return true;
}

////////////////////Radial damage/////////////////

void AGrux::ServerApplyRadialDamage_Implementation(float RDamage,float Radius)
{
	UGameplayStatics::ApplyRadialDamage(GetWorld(), RDamage, this->GetActorLocation(), Radius, nullptr, TArray<AActor*>(), this, false, ECC_Visibility);
	GruxLeftCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GruxRightCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


bool AGrux::ServerApplyRadialDamage_Validate(float RDamage, float Radius)
{
	return true;
}
/////////////////

// Called every frame
void AGrux::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrux::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GruxAnim = Cast<UGruxAnimInstance>(GetMesh()->GetAnimInstance());
	GruxAI = Cast<AGruxAIController>(GetController());
	GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr != GruxAnim)
	{
		GruxAnim->OnMontageEnded.AddDynamic(this, &AGrux::OnAttackMontageEnded);
	}
	GruxLeftCheck->OnComponentBeginOverlap.AddDynamic(this, &AGrux::AttackCheckOverlap);
	GruxRightCheck->OnComponentBeginOverlap.AddDynamic(this, &AGrux::AttackCheckOverlap);


}

// Called to bind functionality to input
void AGrux::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void AGrux::AttackCheckOverlap(UPrimitiveComponent* OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FVector OverlapLocation = OverlappedComp->GetComponentLocation();
	
	if (OtherActor != this)
	{
		LOG(Warning, TEXT("Damage:%d"),Damage);
		ServerApplyDamage(OtherActor, Damage, this);
	}
}

float AGrux::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		GruxHP -= ActualDamage;
		if (GruxHP <= 0.f && !IsDeath)
		{
			GruxDeath();
		}
		if (GruxHP <= GruxMaxHP / 2&&!PowerUP)
		{
			GruxAI->StopAI();
			PowerUP = true;
			Damage *= 1.5;
			GruxAnim->PlayGruxPowerUP();
			GetWorld()->GetTimerManager().SetTimer(timer, this, &AGrux::AIStart, 2.0f, false);
			Particle->Activate(true);
			
		}

	}
		return ActualDamage;
}



void AGrux::Attack()
{
	if (!IsAttacking)
	{
		Damage *= 1.4;
		GruxAnim->PlayAttackMontage();
		IsAttacking = true;	
	}
}

void AGrux::DashAttack()
{
	if (!IsAttacking)
	{
		Damage *= 2.0;
		GruxAnim->PlayAttackMontage2();
		IsAttacking = true;
	}
}

void AGrux::TurnLeft()
{
	if (!IsAttacking)
	{
		GruxAnim->PlayTurnLeft();
		IsAttacking = true;
	}
}

void AGrux::TurnRight()
{
	if (!IsAttacking)
	{
		GruxAnim->PlayTurnRight();
		IsAttacking = true;
	}
}

void AGrux::CastMethor()
{
	if (!IsAttacking)
	{
		GruxAnim->PlayCast();
		IsAttacking = true;
	}
}

void AGrux::FourStrike()
{
	if (!IsAttacking)
	{
		Damage *= 1.5;

		GruxAnim->PlayFourStrike();
		IsAttacking = true;
		
	}
}

void AGrux::DoublePain()
{
	if (!IsAttacking)
	{
		Damage *= 1.3;
		GruxAnim->PlayDoublePain();
		IsAttacking = true;
	}
}

void AGrux::BackJump()
{
	if (!IsAttacking)
	{
		GruxAnim->PlayBackJump();
		IsAttacking = true;
	}
}

void AGrux::Tount()
{
	if (!IsAttacking)
	{
		GruxAnim->PlayTount();
		IsAttacking = true;
	}
}

void AGrux::Quake()
{
	if (!IsAttacking)
	{
		Damage *= 2.0;
		GruxAnim->PlayQuake();
		IsAttacking = true;
	}
}

void AGrux::GruxDeath()
{
	IsDeath = true;
	GruxAnim->PlayGruxDeath();
	GruxAI->StopAI();
	Particle->Deactivate();
	GameMode->EndGame.Broadcast();
}

void AGrux::AIStart()
{
	if(GruxAI!=nullptr)
	GruxAI->StartAI();
}

void AGrux::RadialDamage()
{
	ServerApplyRadialDamage(Damage*2.5, 1000);
}

void AGrux::RadialDamage2()
{
	ServerApplyRadialDamage(Damage*3.0, 2000);
}


void AGrux::OnLeftCollStart() // 노티파이 발생시 공격 컬리전 체크
{
	GruxLeftCheck->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AGrux::OnLeftCollEnd()
{
	GruxLeftCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGrux::OnRightCollStart() 
{
	GruxRightCheck->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AGrux::OnRightCollEnd()
{
	GruxRightCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGrux::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	if (IsAttacking)
	{
		Damage = 500.0f;
		IsAttacking = false;
		OnAttackEnd.Broadcast();
		if (PowerUP) Damage = 750.0f;
	}
	GruxLeftCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GruxRightCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}