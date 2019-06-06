// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RaidGameMode.h"
#include "RaidPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "RaidPlayerController.h"
#include "RaidPlayerState.h"

ARaidGameMode::ARaidGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Characters/BP_RaidPlayer.BP_RaidPlayer_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = ARaidPlayerController::StaticClass();
		PlayerStateClass = ARaidPlayerState::StaticClass();
	}
}
