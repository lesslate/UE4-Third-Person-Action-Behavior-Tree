// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GruxAttack.h"
#include "GruxAIController.h"
#include "Grux.h"

UBTTask_GruxAttack::UBTTask_GruxAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_GruxAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == Grux)
	return EBTNodeResult::Failed;


	Grux->Attack();
	IsAttacking = true;


	Grux->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		LOG(Warning, TEXT("Attack ENd"));
	});
	return EBTNodeResult::InProgress;


}

void UBTTask_GruxAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}




