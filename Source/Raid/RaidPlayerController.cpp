// Fill out your copyright notice in the Description page of Project Settings.

#include "RaidPlayerController.h"
#include "ConstructorHelpers.h"
#include "UI_Result.h"
#include "UI_Death.h"
#include "UI_Menu.h"
#include "UI_HUD.h"
#include "UI_Setting.h"
#include "WidgetComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RaidGameMode.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "RaidGameInstance.h"


ARaidPlayerController::ARaidPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUI_Result> UI_Result_C(TEXT("WidgetBlueprint'/Game/UI/BP_Result.BP_Result_C'"));
	if (UI_Result_C.Succeeded())
	{
		ResultUIClass = UI_Result_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UUI_Death> UI_DEATH(TEXT("WidgetBlueprint'/Game/UI/BP_Death.BP_Death_C'"));
	if (UI_DEATH.Succeeded())
	{
		DeathUIClass = UI_DEATH.Class;
	}

	static ConstructorHelpers::FClassFinder<UUI_Menu> UI_MENU(TEXT("WidgetBlueprint'/Game/UI/BP_Menu.BP_Menu_C'"));
	if (UI_MENU.Succeeded())
	{
		MenuUIClass = UI_MENU.Class;
	}

	static ConstructorHelpers::FClassFinder<UUI_HUD> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/BP_HUDWidget.BP_HUDWidget_C'"));
	if (UI_HUD.Succeeded())
	{
		HUDUIClass = UI_HUD.Class;
	}
}

void ARaidPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddHUDUI();
	AddMenuUI();
	//AddSettingUI();

	ARaidGameMode* GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode != nullptr)
	{
		GameMode->EndGame.AddUObject(this, &ARaidPlayerController::AddResultUITimer);
		GameMode->PlayerDead.AddUObject(this, &ARaidPlayerController::AddDeathUITimer);
	}


}

void ARaidPlayerController::AddResultUITimer()
{
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ARaidPlayerController::AddResultUI, 5.2f, false);
}

void ARaidPlayerController::AddDeathUITimer()
{
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ARaidPlayerController::AddDeathUI, 5.2f, false);
}

void ARaidPlayerController::AddResultUI()
{
	ResultWidget = CreateWidget<UUI_Result>(this, ResultUIClass);
	CHECK(nullptr != ResultWidget);
	ResultWidget->AddToViewport();
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

void ARaidPlayerController::AddDeathUI()
{
	DeathWidget = CreateWidget<UUI_Death>(this, DeathUIClass);
	CHECK(nullptr != DeathWidget);
	DeathWidget->AddToViewport();
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}


void ARaidPlayerController::AddMenuUI()
{
	MenuWidget = CreateWidget<UUI_Menu>(this, MenuUIClass);
	CHECK(nullptr != MenuWidget);
	MenuWidget->AddToViewport();
	MenuWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ARaidPlayerController::AddHUDUI()
{
	HUDWidget = CreateWidget<UUI_HUD>(this, HUDUIClass);
	CHECK(nullptr != HUDWidget);
	HUDWidget->AddToViewport();
	HUDWidget->SetVisibility(ESlateVisibility::Hidden);
}

//void ARaidPlayerController::AddSettingUI()
//{
//	//auto GameInstance = Cast<URaidGameInstance>(GetGameInstance());
//	//SettingUI = GameInstance->SettingWidget;
//	//SettingUI->AddToViewport();
//	//SettingUI->SetVisibility(ESlateVisibility::Hidden);
//}
//
