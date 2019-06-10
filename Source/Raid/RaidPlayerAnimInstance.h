// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "Animation/AnimInstance.h"
#include "RaidPlayer.h"
#include "RaidPlayerAnimInstance.generated.h"



DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FDodgeEnd);

/**
 * 
 */
UCLASS()
class RAID_API URaidPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	URaidPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

	void PlayAttackMontage();
	void PlayAttackMontage2();
	void PlayDashAttack();
	void PlayDodge();
	void JumpToAttackMontageSection(int32 NewSection);
	void PlayDead();
	void PlayHitMontage();


public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FDodgeEnd DodgeEnd;

	UPROPERTY()
	class ARaidPlayer* Player;
private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	UFUNCTION()
	void AnimNotify_OnCollision();

	UFUNCTION()
	void AnimNotify_OnCollisionEnd();

	UFUNCTION()
	void AnimNotify_DodgeEnd();

	FName GetAttackMontageSectionName(int32 Section);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Attack,Meta= (AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* HitMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DashAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* Dodge;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* Dead;
};
