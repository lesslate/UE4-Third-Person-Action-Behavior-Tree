// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Raid.h"
#include "GameFramework/Character.h"
#include "Grux.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class RAID_API AGrux : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGrux();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ARaidGameMode* GameMode;

	void Attack();
	void DashAttack();
	void TurnLeft();
	void TurnRight();
	void CastMethor();
	void FourStrike();
	void DoublePain();
	void BackJump();
	void Tount();
	void Quake();
	

	void GruxDeath();
	void AIStart();
	void RadialDamage();
	void RadialDamage2();

	void OnLeftCollStart();
	void OnLeftCollEnd();
	void OnRightCollStart();
	void OnRightCollEnd();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float GruxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float GruxMaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stat")
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	bool IsDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	bool PowerUP;

	UPROPERTY()
	class UParticleSystem * BuffParticle;

	FOnAttackEndDelegate OnAttackEnd;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
	class UParticleSystemComponent* Particle;

	// ¹«±â Ä¸½¶ ÄÃ¸®Àü1
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UCapsuleComponent* GruxLeftCheck;

	// ¹«±â Ä¸½¶ ÄÃ¸®Àü2
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UCapsuleComponent* GruxRightCheck;
	
	// Grux hit »ç¿îµå
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	class USoundCue* GruxHitSound;

	UPROPERTY()
	class UParticleSystem* GruxHitEffect;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void AttackCheckOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	///////// ServerApplyDamage  //////////////////

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerApplyDamage(AActor* DamagedActor, float Damamge, AActor* DamageCauser);
	void ServerApplyDamage_Implementation(AActor* DamagedActor, float Damamge, AActor* DamageCauser);
	bool ServerApplyDamage_Validate(AActor* DamagedActor, float Damamge, AActor* DamageCauser);

	///////// ServerApplyRadialDamage /////////////
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerApplyRadialDamage(float RDamage, float Radius);
	void ServerApplyRadialDamage_Implementation(float RDamage, float Radius);
	bool ServerApplyRadialDamage_Validate(float RDamage, float Radius);

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
	class UGruxAnimInstance* GruxAnim;

	UPROPERTY()
	class AGruxAIController* GruxAI;

	UPROPERTY()
	FTimerHandle timer;



	//UPROPERTY()
	//class A* GruxAI;
	
};
