// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicatorComponent.h"

#include "CharacterBase.h"
#include "DamageIndicator.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/UserInterfaceSettings.h"
#include "Kismet/GameplayStatics.h"

UDamageIndicatorComponent::UDamageIndicatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	VerticalSpacing = 40.f;
	VerticalOffset = 100.f;
}


// Called when the game starts
void UDamageIndicatorComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDamageIndicatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Viewport Size
	const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	if (ViewportSize.X <= 0 || ViewportSize.Y <= 0) { return; }

	// Get Viewport Scale
	const int32 ViewportX = FGenericPlatformMath::FloorToInt(ViewportSize.X);
	const int32 ViewportY = FGenericPlatformMath::FloorToInt(ViewportSize.Y);
	const float ViewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(ViewportX, ViewportY));
	if (ViewportScale <= 0) { return ; }
	
	// Adjust spawned DamageIndicators Location
	// *They will appear evenly stacked for every screen resolution
	for (int32 i = 1; i < DamageIndicators.Num(); ++i)
	{
		ADamageIndicator* DamageIndicator = DamageIndicators[i];
		const float Offset = (DamageIndicator->GetIndicatorLocation().Size() / 4) / (ViewportSize.X / ViewportScale);

		DamageIndicator->SetActorLocation(DamageIndicator->GetIndicatorLocation() + FVector(0.f, 0.f, i * Offset * VerticalSpacing));
	}
}

void UDamageIndicatorComponent::AppendDamageIndicator(FText& Text, FVector Location)
{
	if (DamageIndicatorClass)
	{
		const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, Location + FVector(0.f, 0.f, VerticalOffset));
		
		ADamageIndicator* NewDamageIndicator = GetWorld()->SpawnActorDeferred<ADamageIndicator>(DamageIndicatorClass, SpawnTransform, GetOwner());
		if (NewDamageIndicator)
		{
			NewDamageIndicator->InitializeDamageIndicator(Text);
			NewDamageIndicator->OnDestroyed.AddDynamic(this, &UDamageIndicatorComponent::OnActorDestroyed);
			UGameplayStatics::FinishSpawningActor(NewDamageIndicator, SpawnTransform);

			DamageIndicators.Insert(NewDamageIndicator, 0);
		}
	}
}

void UDamageIndicatorComponent::OnActorDestroyed(AActor* DestroyedActor)
{
	DamageIndicators.Pop();
}

