// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "HeroBase.generated.h"

UCLASS()
class PROTOTYPE0_API AHeroBase : public ACharacterBase
{
	GENERATED_BODY()
	
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
	** Input Bindings
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
	virtual void Attack() override;
	// Attack - Combo (Mouse Left Click)
	void AttackCombo();
	
	virtual void Die() override;
	
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
	FORCEINLINE void SetComboCounter(const int Counter) { ComboCounter = Counter; }
	FORCEINLINE int GetComboCounter() const { return ComboCounter; }
	FORCEINLINE void SetIsComboActive(const bool IsComboActive) { bIsComboActive = IsComboActive; }
	FORCEINLINE bool GetIsComboActive() const { return bIsComboActive; }
};