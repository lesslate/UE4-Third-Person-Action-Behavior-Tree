// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GoBackward.h"
#include "GruxAIController.h"
#include "Grux.h"
#include "RaidPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


UBTTask_GoBackward::UBTTask_GoBackward()
{
	NodeName = TEXT("Back");
}

EBTNodeResult::Type UBTTask_GoBackward::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Grux)
		return EBTNodeResult::Failed;

	auto Target = Cast<ARaidPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGruxAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector =  Grux->GetActorLocation()-Target->GetActorLocation();
	FVector TargetVector = Grux->GetActorLocation() - LookVector.GetSafeNormal()*(-800.0f);

	Grux->LaunchCharacter(TargetVector, false, false);
	return EBTNodeResult::Succeeded;
}



