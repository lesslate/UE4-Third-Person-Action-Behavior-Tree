// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_HUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "RaidPlayerStatComponent.h"
#include "RaidPlayer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RaidGameMode.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void UUI_HUD::BindCharacterStat(URaidPlayerStatComponent * CharacterStat)
{
	CHECK(nullptr != CharacterStat);
	CurrentCharacterStat = CharacterStat;
	//CharacterStat->OnHPChanged.AddUObject(this, &UABHUDWidget::UpdateCharacterStat);
}

void UUI_HUD::NativeConstruct()
{
	Super::NativeConstruct();
	ARaidGameMode* GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode != nullptr)
	{
		GameMode->StartGame.AddUObject(this, &UUI_HUD::VisibleBossHUD);
		GameMode->EndGame.AddUObject(this, &UUI_HUD::HideBossHUD);
	}

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerHP")));
	BossHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossHP")));
	BossName = Cast<UTextBlock>(GetWidgetFromName(TEXT("BossName")));
	CHECK(nullptr != HPBar);
	CHECK(nullptr!=BossHPBar)


}

void UUI_HUD::UpdateCharacterStat()
{
	CHECK(CurrentCharacterStat.IsValid());

	//HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void UUI_HUD::VisibleBossHUD()
{
	BossHPBar->SetVisibility(ESlateVisibility::Visible);
	BossName->SetVisibility(ESlateVisibility::Visible);
}

void UUI_HUD::HideBossHUD()
{
	BossHPBar->SetVisibility(ESlateVisibility::Hidden);
	BossName->SetVisibility(ESlateVisibility::Hidden);
}