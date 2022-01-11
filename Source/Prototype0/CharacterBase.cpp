// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "DamageIndicatorComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Damage Indicator Component
	SetDamageIndicatorComponent(CreateDefaultSubobject<UDamageIndicatorComponent>(TEXT("Damage Indicator")));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
	bIsAttacking = false;
	bCanDamage = false;
	bIsDead = false;

	// Bind OnPlayMontageNotifyBegin Delegate
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ACharacterBase::OnMontageNotifyBegin);

	// Bind OnPlayMontageNotifyEnd Delegate
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &ACharacterBase::OnMontageNotifyEnd);
	
	// Bind OnTakeAnyDamage Delegate 
	OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::OnDamageTaken);
}

// Called every frame
void ACharacterBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	bCanDamage = true;
}

void ACharacterBase::OnMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	bCanDamage = false;
}

void ACharacterBase::Attack()
{
}

void ACharacterBase::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage != 0 && GetCurrentHealth() > 0)
	{
		// Decrease Health
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - Damage, 0.0f, GetMaxHealth()));

		// Spawn Damage Indicators
		const FString DamageString = FString::SanitizeFloat(Damage, 0);
		FText DamageText = FText::FromString(DamageString);
		GetDamageIndicatorComponent()->AppendDamageIndicator(DamageText, GetActorLocation());

		// Check if Character is dead
		if (GetCurrentHealth() <= 0)
		{
			Die();
		}
	}
}

void ACharacterBase::Die()
{
	bIsDead = true;

	// Remove Collisions
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	
	// Play Death Montage
	const int32 DeathMontageToPlay = FMath::RandRange(1, DeathMontages.Num());
	if (DeathMontages[DeathMontageToPlay - 1])
	{
		PlayAnimMontage(DeathMontages[DeathMontageToPlay - 1]);
	}
}
