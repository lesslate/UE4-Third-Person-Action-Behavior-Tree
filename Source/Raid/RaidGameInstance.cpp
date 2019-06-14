// Fill out your copyright notice in the Description page of Project Settings.

#include "RaidGameInstance.h"
#include "ConstructorHelpers.h"
#include "UI_Setting.h"

URaidGameInstance::URaidGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUI_Setting> UI_SETTING_C(TEXT("WidgetBlueprint'/Game/GameMode/Title/BP_Setting.BP_Setting_C'"));
	if (UI_SETTING_C.Succeeded())
	{
		SettingUIClass = UI_SETTING_C.Class;
	}
}

void URaidGameInstance::Init()
{
	Super::Init();

	AddSettingUI();
}

void URaidGameInstance::AddSettingUI()
{
	SettingWidget = CreateWidget<UUI_Setting>(this, SettingUIClass);
	CHECK(nullptr != SettingWidget);
}
