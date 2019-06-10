// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "GameFramework/PlayerController.h"
#include "RaidPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RAID_API ARaidPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARaidPlayerController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUI_HUD> HUDWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void VisibleHUD();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UUI_HUD* HUDWidget;

};
