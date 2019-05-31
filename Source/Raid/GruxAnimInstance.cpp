// Fill out your copyright notice in the Description page of Project Settings.

#include "GruxAnimInstance.h"
#include "ConstructorHelpers.h"

UGruxAnimInstance::UGruxAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/RightAttack.RightAttack'"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		RightAttack = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE2(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/Stampede_Knockup_Montage.Stampede_Knockup_Montage'"));
	if (ATTACK_MONTAGE2.Succeeded())
	{
		DashAttackMontage = ATTACK_MONTAGE2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> TURNLEFT(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/Turn_Left_180_Montage.Turn_Left_180_Montage'"));
	if (TURNLEFT.Succeeded())
	{
		TurnLeft = TURNLEFT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> TURNRIGHT(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/Turn_Right_180_Montage.Turn_Right_180_Montage'"));
	if (TURNRIGHT.Succeeded())
	{
		TurnRight = TURNRIGHT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> CAST(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/Cast_Montage.Cast_Montage'"));
	if (CAST.Succeeded())
	{
		CastMontage = CAST.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> START(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/StartMontage.StartMontage'"));
	if (START.Succeeded())
	{
		StartMontage = START.Object;
	}
	
}


void UGruxAnimInstance::PlayAttackMontage()
{
	Montage_Play(RightAttack, 1.0f);
}

void UGruxAnimInstance::PlayAttackMontage2()
{
	Montage_Play(DashAttackMontage, 1.0f);
}

void UGruxAnimInstance::PlayTurnLeft()
{
	Montage_Play(TurnLeft, 1.0f);
}

void UGruxAnimInstance::PlayTurnRight()
{
	Montage_Play(TurnRight, 1.0f);
}

void UGruxAnimInstance::PlayCast()
{
	Montage_Play(CastMontage, 1.0f);
}

void UGruxAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

}
