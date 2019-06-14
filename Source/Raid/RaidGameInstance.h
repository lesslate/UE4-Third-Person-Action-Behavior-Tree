// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "Engine/GameInstance.h"
#include "RaidGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API URaidGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	URaidGameInstance();

protected:
	virtual void Init() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddSettingUI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUI_Setting> SettingUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	class UUI_Setting* SettingWidget;
};
