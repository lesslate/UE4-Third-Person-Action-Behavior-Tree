// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Default = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	RootComponent = Default;

	Block = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxBlock"));
	Block->SetupAttachment(RootComponent);
	LockParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	LockParticle->SetupAttachment(RootComponent);
	
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

