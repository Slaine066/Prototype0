// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "CharacterBase.h"
#include "HeroBase.h"
#include "MobBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// Setup WeaponState
	SetWeaponState(EWeaponState::Ews_Free);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// Check if this Weapon is Free
	// If so, Set Hero's Overlapping Item
	if (GetWeaponState() == EWeaponState::Ews_Free)
	{
		if (OtherActor)
		{
			AHeroBase* Hero = Cast<AHeroBase>(OtherActor);
			if (Hero)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hero Overlaps with Weapon Begin"));
				Hero->SetOverlappingItem(this);
			}
		}
	}

	// Check if this Weapon is Equipped
	// If so, Do Damage to the Overlapped Character
	if (GetWeaponState() == EWeaponState::Ews_Equipped)
	{
		if (OtherActor && OtherActor != GetWeaponOwner() && GetWeaponOwner()->bCanDamage)
		{
			ACharacterBase* Character = Cast<ACharacterBase>(OtherActor);
			if (Character)
			{
				UGameplayStatics::ApplyDamage(Character, Damage, GetInstigatorController(), GetWeaponOwner(), DamageType);
				UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitParticle, GetActorLocation());
			}
		}
	}
}

void AWeaponBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	// Check if this Item is not already Equipped
	if (GetWeaponState() == EWeaponState::Ews_Free)
	{
		if (OtherActor)
		{
			AHeroBase* Hero = Cast<AHeroBase>(OtherActor);
			if (Hero)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hero Overlaps with Weapon Begin"));
				Hero->SetOverlappingItem(nullptr);
			}
		}
	}
}

void AWeaponBase::OnInteract(AHeroBase* Hero)
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Picks Weapon Up"));
	
	if (Hero && GetWeaponState() == EWeaponState::Ews_Free)
	{
		const USkeletalMeshSocket* WeaponSocket = Hero->GetMesh()->GetSocketByName("Hand_RSocket");
		if (WeaponSocket)
		{
			WeaponSocket->AttachActor(this, Hero->GetMesh());

			// Destroy previous Weapon
			if (Hero->GetWeaponEquipped())
			{
				Hero->GetWeaponEquipped()->Destroy();
			}
		
			// Equip Weapon
			Hero->SetWeaponEquipped(this, Hero);
			Hero->SetOverlappingItem(nullptr);
		
			bShouldAnimate = false;
			WeaponState = EWeaponState::Ews_Equipped;

			// Play Sound
			if (OnEquipWeaponSound)
			{
				UGameplayStatics::PlaySound2D(this, OnEquipWeaponSound);
			}
		}
	}
}
