// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_LDRandomNumber.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "GruxAIController.h"
#include "Grux.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_LDRandomNumber::UBTService_LDRandomNumber()
{
	NodeName = TEXT("LD_CreateRandomNumber");
	Interval = 1.0f;

	bNotifyBecomeRelevant = true;
}

void UBTService_LDRandomNumber::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	int x = 0;
	x = FMath::RandRange(1, 100);



	if (x <= 40)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber2, 1);
	}
	else if (x <= 80)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber2, 2);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AGruxAIController::SelectAttackNumber2, 3);
	}

}




