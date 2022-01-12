// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageIndicator.h"
#include "Blueprint/UserWidget.h"
#include "DamageIndicatorWidget.generated.h"

class UTextBlock;
UCLASS(Abstract)
class PROTOTYPE0_API UDamageIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	void InitializeDamageIndicator(FText Text, EDamageIndicatorType Type) const;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DamageText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Floating;

	FWidgetAnimationDynamicEvent OnAnimFinished;
};
