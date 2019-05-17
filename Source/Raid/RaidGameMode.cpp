// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RaidGameMode.h"
#include "RaidCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARaidGameMode::ARaidGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Characters/BP_RaidPlayer.BP_RaidPlayer_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
