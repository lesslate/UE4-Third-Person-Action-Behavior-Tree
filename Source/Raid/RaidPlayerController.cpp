// Fill out your copyright notice in the Description page of Project Settings.

#include "RaidPlayerController.h"
#include "ConstructorHelpers.h"
#include "UI_HUD.h"
#include "WidgetComponent.h"

ARaidPlayerController::ARaidPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUI_HUD> UI_HUD_C(TEXT("WidgetBlueprint'/Game/UI/BP_HUDWidget.BP_HUDWidget_C'"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}

void ARaidPlayerController::VisibleHUD()
{
	CHECK(nullptr != HUDWidget);
	HUDWidget->SetVisibility(ESlateVisibility::Visible);
}

void ARaidPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UUI_HUD>(this, HUDWidgetClass);
	CHECK(nullptr != HUDWidget);
	HUDWidget->AddToViewport();
	HUDWidget->SetVisibility(ESlateVisibility::Hidden);
}
