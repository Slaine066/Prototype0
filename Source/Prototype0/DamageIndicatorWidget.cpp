// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicatorWidget.h"

#include "Components/TextBlock.h"

void UDamageIndicatorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DesignSizeMode = EDesignPreviewSizeMode::Desired;

	// Bind OnAnimationFinished
	BindToAnimationFinished(Floating, OnAnimFinished);
}

void UDamageIndicatorWidget::InitializeDamageIndicator(const FText Text) const
{
	DamageText->SetText(Text);
}

void UDamageIndicatorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	// Play Animation
	if (Floating)
	{
		PlayAnimation(Floating);
	}
}