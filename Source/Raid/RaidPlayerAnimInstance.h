// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RaidPlayerAnimInstance.generated.h"

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

	void PlayAttackMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Attack,Meta= (AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;
};
