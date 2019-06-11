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
	TSubclassOf<class UUI_Result> ResultUIClass;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddResultUI();

	
	void AddResultUITimer();

	void SetInputGameUIMode();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UUI_Result* ResultWidget;

};
