// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageIndicatorComponent.h"
#include "GameFramework/Actor.h"
#include "DamageIndicator.generated.h"


UCLASS()
class PROTOTYPE0_API ADamageIndicator : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText DamageText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EDamageIndicatorType DamageIndicatorType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector IndicatorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Widget;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ADamageIndicator();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void InitializeDamageIndicator(const FText& Text, EDamageIndicatorType Type);

	UFUNCTION()
	void AnimFinished();

	FORCEINLINE FVector GetIndicatorLocation() const { return IndicatorLocation; }
};
