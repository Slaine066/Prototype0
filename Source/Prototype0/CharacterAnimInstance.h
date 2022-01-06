// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

UCLASS()
class PROTOTYPE0_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	void CheckHero();

public:
	// Similar to BeginPlay, but for UAnimInstance
	virtual void NativeInitializeAnimation() override;

	/*
	** Public Properties
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHeroBase* Hero;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	USoundBase* FootstepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	USoundBase* AttackVoice1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	USoundBase* AttackVoice2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	USoundBase* AttackVoice3;

	/*
	** Public Methods
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void UpdateSpeed();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void PlayFootstepSound();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AttackCombo();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PlayAttackVoice();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Die();
};
