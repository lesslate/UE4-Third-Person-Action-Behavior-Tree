// Fill out your copyright notice in the Description page of Project Settings.

#include "RaidPlayerAnimInstance.h"
#include "RaidPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ConstructorHelpers.h"

URaidPlayerAnimInstance::URaidPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/InPlace/AttackMontage_2.AttackMontage_2'"));
	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}
}

void URaidPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		IsInAir = Pawn->GetMovementComponent()->IsFalling();
	}
	
}

void URaidPlayerAnimInstance::PlayAttackMontage()
{
		Montage_Play(AttackMontage, 1.0f);
}
