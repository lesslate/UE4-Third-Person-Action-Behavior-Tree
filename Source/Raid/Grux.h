// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "GameFramework/Character.h"
#include "Grux.generated.h"

UCLASS()
class RAID_API AGrux : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGrux();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attack();
	void Attack2();
	void Attack3();
	void Run();
	void Walk();
	void Death();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;

	//UPROPERTY()
	//class U* GruxAnim;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	float HP;

	UPROPERTY(VisibleAnywhere)
	bool IsDeath;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	//UPROPERTY()
	//class A* GruxAI;

	
};
