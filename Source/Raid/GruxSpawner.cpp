// Fill out your copyright notice in the Description page of Project Settings.

#include "GruxSpawner.h"
#include "Grux.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RaidGameMode.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
AGruxSpawner::AGruxSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGruxSpawner::BeginPlay()
{
	Super::BeginPlay();
	ARaidGameMode* GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode != nullptr)
	{
		GameMode->StartGame.AddUObject(this, &AGruxSpawner::GruxSpawn);
	}
}

void AGruxSpawner::GruxSpawn()
{
	UWorld* world = GetWorld();
	CHECK(GruxClass);
	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator(0, 0, 0);
		FVector  SpawnLocation = GetActorLocation();

		world->SpawnActor<AActor>(GruxClass, SpawnLocation, rotator, SpawnParams);
	}
}