// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
	
public:
	UBTTask_TurnToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
