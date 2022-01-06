// Fill out your copyright notice in the Description page of Project Settings.


#include "MobBase.h"

#include "MobAIController.h"
#include "WeaponBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AMobBase::AMobBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMobBase::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponClass)
	{
		// Setup Weapon
		SetWeaponEquipped(GetWorld()->SpawnActor<AWeaponBase>(WeaponClass), this);
	
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_RSocket");
		if (WeaponSocket)
		{
			WeaponSocket->AttachActor(GetWeaponEquipped(), GetMesh());
			GetWeaponEquipped()->bShouldAnimate = false;
			GetWeaponEquipped()->SetWeaponState(EWeaponState::Ews_Equipped);
		}
	}
	
	bIsAttacking = false;

	// Bind OnMontageEnded Delegate
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AMobBase::OnMontageEnded);
}

// Called every frame
void AMobBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMobBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMobBase::Attack()
{
	if (!bIsDead)
	{
		bIsAttacking = true;
	
		const int32 AttackMontageToPlay = FMath::RandRange(1, 2);
	
		if (AttackMontageToPlay == 1 && AttackMontage1)
		{
			PlayAnimMontage(AttackMontage1);
		}
	
		if (AttackMontageToPlay == 2 && AttackMontage2)
		{
			PlayAnimMontage(AttackMontage2);
		}
	}
}

void AMobBase::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
}

void AMobBase::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* Damage1, AController* InstigatedBy,
	AActor* DamageCauser)
{
    if (Damage != 0 && GetCurrentHealth() > 0)
    {
    	UE_LOG(LogTemp, Warning, TEXT("Mob Takes Damage"));
    	// Decrease Health
    	SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - Damage, 0.0f, GetMaxHealth()));

    	// Check if Character is dead
    	if (GetCurrentHealth() <= 0)
    	{
    		Die();
    	}
    }
}

void AMobBase::Die()
{
	bIsDead = true;
	
	AMobAIController* MobAIController = Cast<AMobAIController>(GetController());
	if (MobAIController)
	{
		MobAIController->GetBehaviorTreeComponent()->StopTree(EBTStopMode::Type::Safe);
	}

	const int32 DeathMontageToPlay = FMath::RandRange(1, 2);
	
	if (DeathMontageToPlay == 1 && DeathMontage1)
	{
		PlayAnimMontage(DeathMontage1);
	}
	
	if (DeathMontageToPlay == 2 && DeathMontage2)
	{
		PlayAnimMontage(DeathMontage2);
	}
}