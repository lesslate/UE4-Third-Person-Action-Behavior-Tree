// Fill out your copyright notice in the Description page of Project Settings.

#include "RaidPlayerController.h"
#include "ConstructorHelpers.h"
#include "UI_Result.h"
#include "WidgetComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RaidGameMode.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"

ARaidPlayerController::ARaidPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUI_Result> UI_Result_C(TEXT("WidgetBlueprint'/Game/UI/BP_Result.BP_Result_C'"));
	if (UI_Result_C.Succeeded())
	{
		ResultUIClass = UI_Result_C.Class;
	}
}

//void ARaidPlayerController::VisibleHUD()
//{
//	CHECK(nullptr != HUDWidget);
//	HUDWidget->SetVisibility(ESlateVisibility::Visible);
//}


void ARaidPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ARaidGameMode* GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode != nullptr)
	{
		GameMode->EndGame.AddUObject(this, &ARaidPlayerController::AddResultUITimer);
		//GameMode->EndGame.AddUObject(this, &ARaidPlayerController::SetInputGameUIMode);
	}

}

void ARaidPlayerController::AddResultUITimer()
{
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ARaidPlayerController::AddResultUI, 5.2f, false);
}

void ARaidPlayerController::AddResultUI()
{
	ResultWidget = CreateWidget<UUI_Result>(this, ResultUIClass);
	CHECK(nullptr != ResultWidget);
	ResultWidget->AddToViewport();
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

void ARaidPlayerController::SetInputGameUIMode()
{
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

