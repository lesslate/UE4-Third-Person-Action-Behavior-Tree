// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_FindPlayer.h"
#include "GruxAIController.h"
#include "RaidPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Grux.h"


UBTService_FindPlayer::UBTService_FindPlayer()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_FindPlayer::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();

	auto GruxAI = Cast<AGruxAIController>(OwnerComp.GetAIOwner());
	DetectRadius = GruxAI->Radius;

	auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());


	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			ARaidPlayer* Player = Cast<ARaidPlayer>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGruxAIController::TargetKey, Player); // Å¸°Ù ÀúÀå

				
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AGruxAIController::TargetKey, nullptr);
	}
	
}