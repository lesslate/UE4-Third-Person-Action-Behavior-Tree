// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_HUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "RaidPlayerStatComponent.h"
#include "RaidPlayer.h"

void UUI_HUD::BindCharacterStat(URaidPlayerStatComponent * CharacterStat)
{
	CHECK(nullptr != CharacterStat);
	CurrentCharacterStat = CharacterStat;
	//CharacterStat->OnHPChanged.AddUObject(this, &UABHUDWidget::UpdateCharacterStat);
}

void UUI_HUD::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerHP")));
	CHECK(nullptr != HPBar);


}

void UUI_HUD::UpdateCharacterStat()
{
	CHECK(CurrentCharacterStat.IsValid());

	//HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

