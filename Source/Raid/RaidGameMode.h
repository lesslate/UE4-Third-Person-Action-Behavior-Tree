// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Raid.h"
#include "GameFramework/GameModeBase.h"
#include "RaidGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FPlayerDead);

UCLASS(minimalapi)
class ARaidGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARaidGameMode();

	FPlayerDead PlayerDead;
};



