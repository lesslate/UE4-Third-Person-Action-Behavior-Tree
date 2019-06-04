// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_LDRandomNumber.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTService_LDRandomNumber : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_LDRandomNumber();


protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
