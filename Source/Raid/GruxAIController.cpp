// Fill out your copyright notice in the Description page of Project Settings.

#include "GruxAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "ConstructorHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



const FName AGruxAIController::Distance(TEXT("Distance"));
const FName AGruxAIController::TargetKey(TEXT("TargetKey"));
const FName AGruxAIController::Direction(TEXT("Direction"));
const FName AGruxAIController::SelectNumber(TEXT("SelectNumber"));

AGruxAIController::AGruxAIController()
{
	// BlackBoard 초기화
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/BB_Grux.BB_Grux'"));
	if (BBObject.Succeeded())
	{
		BBGrux = BBObject.Object;
	}
	// BehaviorTree 초기화
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_Grux.BT_Grux'"));
	if (BTObject.Succeeded())
	{
		BTGrux = BTObject.Object;
	}
	Radius = 1500;
}

void AGruxAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	if (!RunBehaviorTree(BTGrux))
	{
		LOG(Warning, TEXT("BT NOT FOUND"));
	}
}

void AGruxAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
		
	}
}

void AGruxAIController::StartAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StartTree(*this->BTGrux, EBTExecutionMode::Looped);
	}
}


