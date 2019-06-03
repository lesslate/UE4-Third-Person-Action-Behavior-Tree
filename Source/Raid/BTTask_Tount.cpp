// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Tount.h"
#include "GruxAIController.h"
#include "Grux.h"


UBTTask_Tount::UBTTask_Tount()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Tount::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == Grux)
		return EBTNodeResult::Failed;


	Grux->Tount();
	IsAttacking = true;


	Grux->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;

	});
	return EBTNodeResult::InProgress;


}

void UBTTask_Tount::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}





