// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_TurnRight.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTTaskNode_TurnRight : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_TurnRight();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;

};