// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

class UUserWidget;

UCLASS()
class PROTOTYPE0_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> OverlayClass;

	UPROPERTY()
	UUserWidget* Overlay;

protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
