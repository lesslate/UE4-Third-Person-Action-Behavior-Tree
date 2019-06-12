// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorTrigger.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RaidGameMode.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Sound/SoundCue.h"

// Sets default values
ADoorTrigger::ADoorTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Default = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	RootComponent = Default;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundCue>LOCK(TEXT("SoundCue'/Game/Sound/GruxSound/GateLock_Cue.GateLock_Cue'"));
	if (LOCK.Succeeded())
	{
		LockCue = LOCK.Object;
	}
}


// Called when the game starts or when spawned
void ADoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorTrigger::AttackCheckOverlap);
	GameMode = Cast<ARaidGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

// Called every frame
void ADoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorTrigger::AttackCheckOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (nullptr != GameMode)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LockCue);
		GameMode->StartGame.Broadcast();
		Destroy();
	}
}

