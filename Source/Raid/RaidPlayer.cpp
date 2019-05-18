// Fill out your copyright notice in the Description page of Project Settings.

#include "RaidPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Components/StaticMeshComponent.h"
#include "RaidPlayerAnimInstance.h"

// Sets default values
ARaidPlayer::ARaidPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 350.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	bUseControllerRotationYaw = false;

	// 스프링암 생성
	TPSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSpringArm"));
	TPSpringArm->SetupAttachment(RootComponent);
	TPSpringArm->TargetArmLength = 300.0f;
	TPSpringArm->bUsePawnControlRotation = true;
	TPSpringArm->bInheritPitch = true;
	TPSpringArm->bInheritRoll = true;
	TPSpringArm->bInheritYaw = true;
	TPSpringArm->bDoCollisionTest = true;


	// 카메라 생성
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(TPSpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// 애니메이션 블루프린트 속성지정
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("AnimBlueprint'/Game/Characters/BP_RaidPlayerAnim.BP_RaidPlayerAnim_C'")); // _C를 붙여 클래스정보를 가져옴
	if (PlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);
	}

	// 스켈레탈 메시 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMesh(TEXT("SkeletalMesh'/Game/TwinbladesAnimsetBase/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (PlayerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMesh.Object);
	}

	//무기 소켓 생성
	BladeLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BladeLeft"));
	BladeLeft->SetupAttachment(GetMesh(), TEXT("BladeLeft"));

	BladeRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BladeRight"));
	BladeRight->SetupAttachment(GetMesh(), TEXT("BladeRight"));

	// 달리기 속도 배수
	SprintSpeedMultiplier = 2.0f;

	IsAttacking = false;

	MaxCombo = 4;
	
}

// Called when the game starts or when spawned
void ARaidPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARaidPlayer::PostInitializeComponents()
{	
	Super::PostInitializeComponents();
	PlayerAnim = Cast<URaidPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
	if (nullptr != PlayerAnim)
	{
		PlayerAnim->OnMontageEnded.AddDynamic(this, &ARaidPlayer::OnAttackMontageEnded);

		PlayerAnim->OnNextAttackCheck.AddLambda([this]()->void {
			CanNextCombo = false;

			if (IsComboInputOn)
			{
				AttackStartComboState();
				PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
			}
		});
	}
}

// Called every frame
void ARaidPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARaidPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARaidPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARaidPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ARaidPlayer::StartSprintServer);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ARaidPlayer::StopSprintServer);

	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ARaidPlayer::Attack);

}

void ARaidPlayer::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ARaidPlayer::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}


void ARaidPlayer::StartSprintServer_Implementation()
{
	StartSprintMulticast();
}

bool ARaidPlayer::StartSprintServer_Validate()
{
	return true;
}

void ARaidPlayer::StartSprintMulticast_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void ARaidPlayer::StopSprintServer_Implementation()
{
	StopSprintMulticast();
}

bool ARaidPlayer::StopSprintServer_Validate()
{
	return true;
}

void ARaidPlayer::StopSprintMulticast_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}



void ARaidPlayer::Attack()
{

	if (IsAttacking)
	{
		CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		CHECK(CurrentCombo == 0);
		AttackStartComboState();
		PlayerAnim->PlayAttackMontage();
		PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}

}

void ARaidPlayer::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ARaidPlayer::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void ARaidPlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	CHECK(IsAttacking);
	CHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();

}
