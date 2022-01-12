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

void UDamageIndicatorWidget::InitializeDamageIndicator(const FText Text, EDamageIndicatorType Type) const
{
	DamageText->SetText(Text);

	switch (Type)
	{
		case EDamageIndicatorType::Edit_Hero:
			{
				const FSlateColor Red = FSlateColor(FLinearColor(255.f, 0.f, 0.f, 1.0f));
				DamageText->SetColorAndOpacity(Red);
				break;
			}
		case EDamageIndicatorType::Edit_Mob:
			{
				const FSlateColor Yellow = FSlateColor(FLinearColor(255.f, 255.f, 0.f, 1.0f));
				DamageText->SetColorAndOpacity(Yellow);
				break;
			}
		default:
			UE_LOG(LogTemp, Warning, TEXT("InitializeDamageIndicator() EDamageIndicatorType Default"));
	}
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