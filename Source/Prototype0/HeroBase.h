// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "HeroBase.generated.h"

UCLASS()
class PROTOTYPE0_API AHeroBase : public ACharacterBase
{
	GENERATED_BODY()

	/*
	** Private Properties
	*/
	// Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// Perception Stimuli Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* StimuliComponent;
	
	// Item Overlapping with the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	class AItemBase* OverlappingItem;

	// Weapon Class
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<AWeaponBase> WeaponClass;

	// Shield Class
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<AShieldBase> ShieldClass;

	// Check if the player is already attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	// Contains Integer related to the combo attack to perform
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	int ComboCounter;

	// If true, AttackCombo() will be executed on player attack
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsComboActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AHeroBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	** Public Properties
	*/
	// Attacks Montages
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	class UAnimMontage* AttackMontage1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	class UAnimMontage* AttackMontage2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	class UAnimMontage* AttackMontage3;

	// Deaths Montages
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* DeathMontage1;

	/*
	** Public Methods
	*/
	// Move Forward (W) - Move Backward (S)
	void MoveStraight(float AxisValue);
	// Move Left (A) - Move Right (D) 
	void MoveSide(float AxisValue);
	// Look Vertical (Mouse UP/DOWN)
	void LookVertical(float AxisValue);
	// Look Horizontal (Mouse LEFT/RIGHT)
	void LookHorizontal(float AxisValue); 
	// Interact with Items in the world (E)
	void Interact();
	// Attack (Mouse Left Click)
	void Attack();
	// Attack - Combo (Mouse Left Click)
	void AttackCombo();

	UFUNCTION()
	void Die();
	
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;
	
	/*
	** Getters & Setters
	*/
	// Camera
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	// Item
	FORCEINLINE void SetOverlappingItem(AItemBase* Item) { OverlappingItem = Item; }
	FORCEINLINE AItemBase* GetOverlappingItem() const { return OverlappingItem; }

	// Combat
	FORCEINLINE void SetIsAttacking(const bool IsAttacking) { bIsAttacking = IsAttacking; }
	FORCEINLINE bool GetIsAttacking() const { return bIsAttacking; }
	FORCEINLINE void SetComboCounter(const int Counter) { ComboCounter = Counter; }
	FORCEINLINE int GetComboCounter() const { return ComboCounter; }
	FORCEINLINE void SetIsComboActive(const bool IsComboActive) { bIsComboActive = IsComboActive; }
	FORCEINLINE bool GetIsComboActive() const { return bIsComboActive; }
};
