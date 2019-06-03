// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GoBackward.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UBTTask_GoBackward : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_GoBackward();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
