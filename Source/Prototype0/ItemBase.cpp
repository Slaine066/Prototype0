// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "CharacterBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	// Setup Collisions
	MeshComponent->SetCollisionProfileName(TEXT("Item"));
	MeshComponent->SetSimulatePhysics(false);

	bShouldAnimate = true;

	// Overlap Delegates
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapBegin);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnOverlapEnd);
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldAnimate)
	{
		// Floating Behavior
		FVector ActorLocation = GetActorLocation();
		ActorLocation.Z += FMath::Sin(5 * TimeSinceCreation);
		SetActorLocation(ActorLocation);
		TimeSinceCreation += DeltaTime;
	
		// Rotating Behavior
		FRotator ActorRotation = GetActorRotation();
		ActorRotation.Yaw -= DeltaTime * 100.f;
		SetActorRotation(ActorRotation);
	}
}

void AItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Show UI Component
	// UE_LOG(LogTemp, Warning, TEXT("AItemBase::OnOverlapBegin()"));
}

void AItemBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// TODO: Hide UI Component
	// UE_LOG(LogTemp, Warning, TEXT("AItemBase::OnOverlapEnd()"));
}

void AItemBase::OnInteract(AHeroBase* Hero)
{
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::OnInteract()"));
}
