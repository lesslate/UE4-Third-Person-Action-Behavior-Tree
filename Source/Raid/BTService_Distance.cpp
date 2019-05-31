// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Distance.h"
#include "GruxAIController.h"
#include "RaidPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Grux.h"


UBTService_Distance::UBTService_Distance()
{
	NodeName = TEXT("Distance");
	Interval = 1.0f;
}

void UBTService_Distance::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());

	bool bResult;

	auto Target = Cast<ARaidPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGruxAIController::TargetKey));
	
	if (nullptr == Target)
		return;

	bResult = (Target->GetDistanceTo(ControllingPawn) >= 1000.0f);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AGruxAIController::Distance, bResult);
}

