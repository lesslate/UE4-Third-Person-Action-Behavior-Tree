// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Distance.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTDecorator_Distance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_Distance();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;



};
