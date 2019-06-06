// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GruxDashAttack.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTTask_GruxDashAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GruxDashAttack();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;

};
