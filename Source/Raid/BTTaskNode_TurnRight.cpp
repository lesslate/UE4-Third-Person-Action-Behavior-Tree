// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_TurnRight.h"
#include "GruxAIController.h"
#include "Grux.h"

UBTTaskNode_TurnRight::UBTTaskNode_TurnRight()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTaskNode_TurnRight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == Grux)
		return EBTNodeResult::Failed;


	Grux->TurnRight();
	IsAttacking = true;


	Grux->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		LOG(Warning, TEXT("Attack ENd"));
	});
	return EBTNodeResult::InProgress;


}

void UBTTaskNode_TurnRight::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}





