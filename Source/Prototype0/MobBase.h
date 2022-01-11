// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "MobBase.generated.h"

class UBehaviorTree;
class UAnimMontage;
class AWeaponBase;

UCLASS()
class PROTOTYPE0_API AMobBase : public ACharacterBase
{
	GENERATED_BODY()
	
	// Behavior Tree
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AMobBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Attack() override;

	virtual void Die() override;
	
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;
	
	// Behavior Tree
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
};
