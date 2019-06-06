// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "Blueprint/UserWidget.h"
#include "UI_HUD.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API UUI_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class URaidPlayerStatComponent* CharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	
private:
	TWeakObjectPtr<class URaidPlayerStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPBar;
};
