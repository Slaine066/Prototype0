// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class AShieldBase;
class AWeaponBase;
class ADamageIndicator;
class UDamageIndicatorComponent;

UCLASS()
class PROTOTYPE0_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	/*
	** Private Properties
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UDamageIndicatorComponent* DamageIndicatorComponent;

	// Weapon Class
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<AWeaponBase> WeaponClass;

	// Shield Class
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<AShieldBase> ShieldClass;
	
	// Weapon held by the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	AWeaponBase* WeaponEquipped;

	// Shield held by the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	AShieldBase* ShieldEquipped;

	// Max Health Statistic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	// Current Health Statistic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	** Public Properties
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bCanDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TArray<UAnimMontage*> DeathMontages;

	/*
	** Public Methods
	*/
	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
	UFUNCTION()
	void OnMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION()
	virtual void Attack();
	
	UFUNCTION()
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	virtual void Die();
	
	/*
	** Getters & Setters
	*/
	FORCEINLINE TSubclassOf<AWeaponBase> GetWeaponClass() const { return WeaponClass; }
	FORCEINLINE TSubclassOf<AShieldBase> GetShieldClass() const { return ShieldClass; }
	
	FORCEINLINE void SetWeaponEquipped(AWeaponBase* Weapon, ACharacterBase* WepOwner) { WeaponEquipped = Weapon; Weapon->SetWeaponOwner(WepOwner); }
	FORCEINLINE AWeaponBase* GetWeaponEquipped() const { return WeaponEquipped; }
	FORCEINLINE void SetShieldEquipped(AShieldBase* Shield) { ShieldEquipped = Shield; }
	FORCEINLINE AShieldBase* GetShieldEquipped() const { return ShieldEquipped; }

	FORCEINLINE void SetMaxHealth(const float Health) { MaxHealth = Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE void SetCurrentHealth(const float Health) { CurrentHealth = Health; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	
	FORCEINLINE void SetDamageIndicatorComponent(UDamageIndicatorComponent* Component) { DamageIndicatorComponent = Component; }
	FORCEINLINE UDamageIndicatorComponent* GetDamageIndicatorComponent() const { return DamageIndicatorComponent; }
};