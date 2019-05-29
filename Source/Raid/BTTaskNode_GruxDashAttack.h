// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_GruxDashAttack.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTTaskNode_GruxDashAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_GruxDashAttack();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;

};
