// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "GameFramework/Actor.h"
#include "DoorTrigger.generated.h"

UCLASS()
class RAID_API ADoorTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class USceneComponent* Default;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class UBoxComponent* BoxTrigger;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ARaidGameMode* GameMode;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* LockCue;

private:
	UFUNCTION()
	void AttackCheckOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
};
