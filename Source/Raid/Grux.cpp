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

// Sets default values
AGrux::AGrux()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 30;

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

	// 오디오 컴포넌트 초기화
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GruxAudio"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(GetMesh());

	// 캡슐 컬리전 생성
	GruxAttackCheck = CreateDefaultSubobject<UCapsuleComponent>(TEXT("GruxAttackCheck1"));
	GruxAttackCheck->SetupAttachment(GetMesh(), TEXT("FX_Trail_L_02"));
	GruxAttackCheck2 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("GruxAttackCheck2"));
	GruxAttackCheck2->SetupAttachment(GetMesh(), TEXT("FX_Trail_R_02"));

	GruxAttackCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GruxAttackCheck2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void AGrux::ServerApplyDamage_Implementation(AActor * DamagedActor, float Damamge, AActor * DamageCauser)
{
	UGameplayStatics::ApplyDamage(DamagedActor, Damage, nullptr, DamageCauser, nullptr);
	GruxAttackCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GruxAttackCheck2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool AGrux::ServerApplyDamage_Validate(AActor * DamagedActor, float Damamge, AActor * DamageCauser)
{
	return true;
}

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
	if (nullptr != GruxAnim)
	{
		GruxAnim->OnMontageEnded.AddDynamic(this, &AGrux::OnAttackMontageEnded);
	}
	GruxAttackCheck->OnComponentBeginOverlap.AddDynamic(this, &AGrux::AttackCheckOverlap);
	GruxAttackCheck2->OnComponentBeginOverlap.AddDynamic(this, &AGrux::AttackCheckOverlap);
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
		ServerApplyDamage(OtherActor, Damage, this);
	}
}

void AGrux::Attack()
{
	if (!IsAttacking)
	{
		GruxAnim->PlayAttackMontage();
		IsAttacking = true;
		
	}
}

void AGrux::DashAttack()
{
	if (!IsAttacking)
	{
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
		GruxAnim->PlayFourStrike();
		IsAttacking = true;
	}
}

void AGrux::DoublePain()
{
	if (!IsAttacking)
	{
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
		GruxAnim->PlayQuake();
		IsAttacking = true;
	}
}

void AGrux::AIStart()
{
	if(GruxAI!=nullptr)
	GruxAI->StartAI();
}

void AGrux::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	if (IsAttacking)
	{
		IsAttacking = false;
		OnAttackEnd.Broadcast();
	}
}