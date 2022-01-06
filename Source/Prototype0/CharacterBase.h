// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class AWeaponBase;
UCLASS()
class PROTOTYPE0_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	/*
	** Private Properties
	*/
	// Weapon held by the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class AWeaponBase* WeaponEquipped;

	// Shield held by the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class AShieldBase* ShieldEquipped;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bCanDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsDead;

	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
	UFUNCTION()
	void OnMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
	UFUNCTION()
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	/*
	** Getters & Setters
	*/
	FORCEINLINE virtual void SetWeaponEquipped(AWeaponBase* Weapon, ACharacterBase* WepOwner) { WeaponEquipped = Weapon; Weapon->SetWeaponOwner(WepOwner); }
	FORCEINLINE virtual AWeaponBase* GetWeaponEquipped() const { return WeaponEquipped; }
	FORCEINLINE virtual void SetShieldEquipped(AShieldBase* Shield) { ShieldEquipped = Shield; }
	FORCEINLINE virtual AShieldBase* GetShieldEquipped() const { return ShieldEquipped; }

	FORCEINLINE virtual void SetMaxHealth(const float Health) { MaxHealth = Health; }
	FORCEINLINE virtual float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE virtual void SetCurrentHealth(const float Health) { CurrentHealth = Health; }
	FORCEINLINE virtual float GetCurrentHealth() { return CurrentHealth; }
};