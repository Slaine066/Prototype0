// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

#include "Blueprint/UserWidget.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (OverlayClass)
	{
		Overlay = CreateWidget<UUserWidget>(this, OverlayClass);
		Overlay->AddToViewport();
		Overlay->SetVisibility(ESlateVisibility::Visible);
	}
}
