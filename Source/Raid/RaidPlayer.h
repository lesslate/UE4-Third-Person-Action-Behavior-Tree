// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RaidPlayer.generated.h"

UCLASS()
class RAID_API ARaidPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaidPlayer();

	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION(Reliable, Server, WithValidation)
	void StartSprintServer();
	void StartSprintServer_Implementation();
	bool StartSprintServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StartSprintMulticast();
	void StartSprintMulticast_Implementation();
	
	UFUNCTION(Reliable, Server, WithValidation)
	void StopSprintServer();
	void StopSprintServer_Implementation();
	bool StopSprintServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void StopSprintMulticast();
	void StopSprintMulticast_Implementation();


	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 스프링암 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* TPSpringArm;

	// 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// 무기1
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* BladeLeft;

	// 무기2
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* BladeRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float SprintSpeedMultiplier;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;
	
	UPROPERTY()
	class URaidPlayerAnimInstance* PlayerAnim;

};
