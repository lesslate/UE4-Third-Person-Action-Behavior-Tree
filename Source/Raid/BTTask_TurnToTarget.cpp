// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_TurnToTarget.h"
#include "GruxAIController.h"
#include "Grux.h"
#include "RaidPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Grux)
		return EBTNodeResult::Failed;

	auto Target = Cast<ARaidPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGruxAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - Grux->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Grux->SetActorRotation(FMath::RInterpTo(Grux->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 0.5f));

	return EBTNodeResult::Succeeded;
}





