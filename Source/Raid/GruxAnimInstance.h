// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "Animation/AnimInstance.h"
#include "GruxAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UGruxAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UGruxAnimInstance();

	void PlayAttackMontage();
	void PlayAttackMontage2();
	void PlayAttackMontage3();
	void PlayDeathMontage();

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DeathMontage;

	
	
};
