// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicator.h"

#include "DamageIndicatorWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADamageIndicator::ADamageIndicator()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Damage Indicator Widget"));
	SetRootComponent(Widget);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetDrawAtDesiredSize(true);
}


// Called when the game starts or when spawned
void ADamageIndicator::BeginPlay()
{
	Super::BeginPlay();

	IndicatorLocation = GetActorLocation();

	UDamageIndicatorWidget* DamageIndicatorWidget = Cast<UDamageIndicatorWidget>(Widget->GetUserWidgetObject());
	if (DamageIndicatorWidget)
	{
		DamageIndicatorWidget->OnAnimFinished.BindDynamic(this, &ADamageIndicator::AnimFinished);
		DamageIndicatorWidget->InitializeDamageIndicator(DamageText, DamageIndicatorType);
	}
	
}

// Called every frame
void ADamageIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADamageIndicator::InitializeDamageIndicator(const FText& Text, const EDamageIndicatorType Type)
{
	DamageText = Text;
	DamageIndicatorType = Type;
}

void ADamageIndicator::AnimFinished()
{
	Destroy();
}

