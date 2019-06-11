// Fill out your copyright notice in the Description page of Project Settings.

#include "RaidGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RaidGameMode.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"


URaidGameInstance::URaidGameInstance()
{

}
void URaidGameInstance::Init()
{
	Super::Init();

	ARaidGameMode* GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode != nullptr)
	{
		GameMode->StartGame.AddUObject(this, &URaidGameInstance::CountStart);
	}
}

void URaidGameInstance::CountStart()
{

}



