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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUI_Death> DeathUIClass;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddResultUI();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddDeathUI();

	void AddResultUITimer();

	void AddDeathUITimer();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UUI_Result* ResultWidget;

	UPROPERTY()
	class UUI_Death* DeathWidget;

};
