// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBase.h"

#include "CharacterBase.h"
#include "HeroBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AShieldBase::AShieldBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShieldBase::BeginPlay()
{
	Super::BeginPlay();

	// Setup ShieldState
	SetShieldState(EShieldState::Ess_Free);
}

// Called every frame
void AShieldBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShieldBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// Check if this Shield is Free
	// If so, set Hero's Overlapping Item
	if (GetShieldState() == EShieldState::Ess_Free)
	{
		if (OtherActor)
		{
			AHeroBase* Hero = Cast<AHeroBase>(OtherActor);
			if (Hero)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hero Overlaps with Shield Begin"));
				Hero->SetOverlappingItem(this);
			}
		}
	}
}

void AShieldBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	// Check if this Item is not already Equipped
	if (GetShieldState() == EShieldState::Ess_Free)
	{
		if (OtherActor)
		{
			AHeroBase* Hero = Cast<AHeroBase>(OtherActor);
			if (Hero)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hero Overlaps with Shield End"));
				Hero->SetOverlappingItem(nullptr);
			}
		}
	}
}

void AShieldBase::OnInteract(AHeroBase* Hero)
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Picks Shield Up"));
	
	if (Hero && GetShieldState() == EShieldState::Ess_Free)
	{
		const USkeletalMeshSocket* ShieldSocket = Hero->GetMesh()->GetSocketByName("Hand_LSocket");
		if (ShieldSocket)
		{
			ShieldSocket->AttachActor(this, Hero->GetMesh());

			// Destroy previous Shield
			if (Hero->GetShieldEquipped())
			{
				Hero->GetShieldEquipped()->Destroy();
			}

			// Equip Shield
			Hero->SetShieldEquipped(this);
			Hero->SetOverlappingItem(nullptr);
			
			bShouldAnimate = false;
			ShieldState = EShieldState::Ess_Equipped;

			// Play Sound
			if (OnEquipShieldSound)
			{
				UGameplayStatics::PlaySound2D(this, OnEquipShieldSound);
			}
		}
	}
}