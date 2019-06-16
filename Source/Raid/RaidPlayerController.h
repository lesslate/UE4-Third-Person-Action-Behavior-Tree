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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUI_Menu> MenuUIClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUI_HUD> HUDUIClass;



	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddResultUI();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddDeathUI();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddMenuUI();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddHUDUI();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddSettingUI();

	void AddResultUITimer();
	void AddDeathUITimer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	class UUI_Result* ResultWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	class UUI_Death* DeathWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	class UUI_Menu* MenuWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	class UUI_HUD* HUDWidget;

};
