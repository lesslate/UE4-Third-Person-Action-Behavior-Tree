// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_RandomNumber.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "GruxAIController.h"
#include "Grux.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_RandomNumber::UBTService_RandomNumber()
{
	NodeName = TEXT("CreateRandomNumber");
	Interval = 1.0f;

	bNotifyBecomeRelevant = true;
}

void UBTService_RandomNumber::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	int x = 0;
	x = FMath::RandRange(1, 100);

	

	if (x <=10)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber, 1);
	}
	else if (x <= 20)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber, 2);
	}
	else if (x <= 50)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber, 3);
	}
	else if (x <= 80)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber, 4);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber, 5);
	}

}
