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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/InPlace/AttackMontage.AttackMontage'"));
	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Dash_Attack(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/RootMotion/Twinblades_Attack09_Montage.Twinblades_Attack09_Montage'"));
	if (Dash_Attack.Succeeded())
	{
		DashAttack = Dash_Attack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage2(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/RootMotion/Twinblades_Attack08_Montage.Twinblades_Attack08_Montage'"));
	if (Attack_Montage2.Succeeded())
	{
		AttackMontage2 = Attack_Montage2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Dodge_Montage(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/RootMotion/Twinblades_Dodge_Montage.Twinblades_Dodge_Montage'"));
	if (Dodge_Montage.Succeeded())
	{
		Dodge = Dodge_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Dead_Montage(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/RootMotion/Twinblades_Dead_Montage.Twinblades_Dead_Montage'"));
	if (Dead_Montage.Succeeded())
	{
		Dead = Dead_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/RootMotion/Twinblades_Hit_Front_Montage.Twinblades_Hit_Front_Montage'"));
	if (HIT.Succeeded())
	{
		HitMontage = HIT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL(TEXT("AnimMontage'/Game/TwinbladesAnimsetBase/RootMotion/Twinblades_SPAttack1_Montage.Twinblades_SPAttack1_Montage'"));
	if (SKILL.Succeeded())
	{
		SkillMontage = SKILL.Object;
	}
}

void URaidPlayerAnimInstance::NativeBeginPlay()
{
	Player = Cast<ARaidPlayer>(TryGetPawnOwner());
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

void URaidPlayerAnimInstance::PlayAttackMontage2()
{
	Montage_Play(AttackMontage2, 1.0f);
}

void URaidPlayerAnimInstance::PlayDead()
{
	Montage_Play(Dead, 1.0f);
}

void URaidPlayerAnimInstance::PlayHitMontage()
{
	Montage_Play(HitMontage, 1.0f);
}

void URaidPlayerAnimInstance::PlaySkill()
{
	Montage_Play(SkillMontage, 1.0f);
}

void URaidPlayerAnimInstance::PlayDashAttack()
{
	Montage_Play(DashAttack, 1.0f);
}

void URaidPlayerAnimInstance::PlayDodge()
{
	Montage_Play(Dodge, 1.0f);
}

void URaidPlayerAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	CHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void URaidPlayerAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void URaidPlayerAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void URaidPlayerAnimInstance::AnimNotify_OnCollision()
{
	Player->OnCollStart();
}

void URaidPlayerAnimInstance::AnimNotify_OnCollisionEnd()
{
	Player->OnCollEnd();
}

void URaidPlayerAnimInstance::AnimNotify_DodgeEnd()
{
	DodgeEnd.Broadcast();
}

FName URaidPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	CHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
