// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_GruxDashAttack.h"
#include "GruxAIController.h"
#include "Grux.h"

UBTTaskNode_GruxDashAttack::UBTTaskNode_GruxDashAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTaskNode_GruxDashAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == Grux)
		return EBTNodeResult::Failed;


	Grux->DashAttack();
	IsAttacking = true;


	Grux->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		LOG(Warning, TEXT("Attack ENd"));
	});
	return EBTNodeResult::InProgress;


}

void UBTTaskNode_GruxDashAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}



