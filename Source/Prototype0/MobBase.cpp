// Fill out your copyright notice in the Description page of Project Settings.


#include "MobBase.h"

#include "DamageIndicator.h"
#include "MobAIController.h"
#include "ShieldBase.h"
#include "WeaponBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMobBase::AMobBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 70.f;
}

// Called when the game starts or when spawned
void AMobBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind OnMontageEnded Delegate
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AMobBase::OnMontageEnded);

	// Setup Collision Profile
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PawnMob"));

	// Setup Weapon
	if (GetWeaponClass())
	{
		// Setup Weapon
		SetWeaponEquipped(GetWorld()->SpawnActor<AWeaponBase>(GetWeaponClass()), this);
	
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_RSocket");
		if (WeaponSocket)
		{
			WeaponSocket->AttachActor(GetWeaponEquipped(), GetMesh());
			GetWeaponEquipped()->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponMob"));
			GetWeaponEquipped()->bShouldAnimate = false;
			GetWeaponEquipped()->SetWeaponState(EWeaponState::Ews_Equipped);
		}
	}

	// Setup Shield
	if (GetShieldClass())
	{
		SetShieldEquipped(GetWorld()->SpawnActor<AShieldBase>(GetShieldClass()));
	
		const USkeletalMeshSocket* ShieldSocket = GetMesh()->GetSocketByName("Hand_LSocket");
		if (ShieldSocket)
		{
			ShieldSocket->AttachActor(GetShieldEquipped(), GetMesh());
			GetShieldEquipped()->bShouldAnimate = false;
			GetShieldEquipped()->SetShieldState(EShieldState::Ess_Equipped);
		}
	}
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
	if (GetWeaponEquipped())
	{
		bIsAttacking = true;
	
		// Play Attack Montage
		const int32 AttackMontageToPlay = FMath::RandRange(1, AttackMontages.Num());

		if (AttackMontages[AttackMontageToPlay - 1])
		{
			PlayAnimMontage(AttackMontages[AttackMontageToPlay - 1]);
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
	UE_LOG(LogTemp, Warning, TEXT("Mob Takes Damage"));
	
    Super::OnDamageTaken(DamagedActor, Damage, Damage1, InstigatedBy, DamageCauser);
}

void AMobBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Mob Dies"));
	Super::Die();
	
	// Stop Behavior Tree
	AMobAIController* MobAIController = Cast<AMobAIController>(GetController());
	if (MobAIController)
	{
		MobAIController->GetBehaviorTreeComponent()->StopTree(EBTStopMode::Type::Safe);
	}
}