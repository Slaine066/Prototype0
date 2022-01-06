// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MobAnimInstance.generated.h"

UCLASS()
class PROTOTYPE0_API UMobAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	void CheckMob();
	
public:
	// Similar to BeginPlay, but for UAnimInstance
	virtual void NativeInitializeAnimation() override;

	/*
	** Public Properties
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMobBase* Mob;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;

	/*
	** Public Methods
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void UpdateSpeed();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Die();
};
