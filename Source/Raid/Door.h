// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class RAID_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class USceneComponent* Default;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class UBoxComponent* Block;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Particle)
	class UParticleSystemComponent* LockParticle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
