// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RaidPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API ARaidPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ARaidPlayerState();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float PlayerHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float PlayerMaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float PlayerDamage;
	
	
};
