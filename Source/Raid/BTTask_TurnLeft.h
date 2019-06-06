// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnLeft.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTTask_TurnLeft : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TurnLeft();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;

};