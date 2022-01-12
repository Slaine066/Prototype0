// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageIndicatorComponent.generated.h"

class ADamageIndicator;

UCLASS()
class PROTOTYPE0_API UDamageIndicatorComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADamageIndicator> DamageIndicatorClass;

	// Amount of Space between each DamageIndicator
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float VerticalSpacing;

	// Amount of Offset when spawning from Character
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float VerticalOffset;

	UPROPERTY()
	TArray<ADamageIndicator*> DamageIndicators;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UDamageIndicatorComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void AppendDamageIndicator(FText& Text, FVector Location);

	UFUNCTION()
	void OnActorDestroyed(AActor* DestroyedActor);
};
