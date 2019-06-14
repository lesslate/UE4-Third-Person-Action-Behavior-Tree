// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
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
	void Jump();
	void StopJumping();
	void PlayerDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ARaidGameMode* GameMode;

	//////////     Sprint   //////////////////////

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

	////////////   Attack    //////////////////////

	UFUNCTION(Reliable, Server, WithValidation)
	void AttackServer();
	void AttackServer_Implementation();
	bool AttackServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void AttackMulticast();
	void AttackMulticast_Implementation();

	////////////   Attack2  //////////////////////

	UFUNCTION(Reliable, Server, WithValidation)
	void AttackServer2();
	void AttackServer2_Implementation();
	bool AttackServer2_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void AttackMulticast2();
	void AttackMulticast2_Implementation();
	
	///////////    Combo  ///////////////////////////

	UFUNCTION(Reliable, Server, WithValidation)
	void ComboServer();
	void ComboServer_Implementation();
	bool ComboServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void ComboMulticast();
	void ComboMulticast_Implementation();

	///////// ServerApplyDamage  //////////////////

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerApplyDamage(AActor* DamagedActor, float Damamge, AActor* DamageCauser);
	void ServerApplyDamage_Implementation(AActor* DamagedActor, float Damamge, AActor* DamageCauser);
	bool ServerApplyDamage_Validate(AActor* DamagedActor, float Damamge, AActor* DamageCauser);

	///////// Dodge  //////////////////

	UFUNCTION(Reliable, Server, WithValidation)
	void DodgeServer();
	void DodgeServer_Implementation();
	bool DodgeServer_Validate();

	UFUNCTION(Reliable, NetMulticast)
	void DodgeMulticast();
	void DodgeMulticast_Implementation();

	/////////////////////////////////////////////////
	void AttackStartComboState();
	void AttackEndComboState();

	void OnCollStart();
	void OnCollEnd();

	void DodgeEndState();

	UPROPERTY()
	bool IsDeath;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float PlayerHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float PlayerMaxHP;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class URaidPlayerStatComponent* CharacterStat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

	// hit 사운드
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* HitSound;

	UPROPERTY()
	class UParticleSystem* PlayerHitEffect;

	// 캡슐 컬리전
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UCapsuleComponent* AttackCheck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float SprintSpeedMultiplier;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Character Stat")
	float Damage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsHit;

	UPROPERTY(Replicated,VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(Replicated,VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class URaidPlayerAnimInstance* PlayerAnim;

	UPROPERTY()
	bool IsInAir;

	UPROPERTY()
	bool IsRun;

	
	UPROPERTY()
	bool IsDodge;

	UFUNCTION()
	void AttackCheckOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
