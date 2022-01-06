// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class PROTOTYPE0_API AItemBase : public AActor
{
	GENERATED_BODY()

	// SceneComponent will be the RootComponent
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	// MeshComponent
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Item time passed since creation (used in the Float behavior)
	UPROPERTY()
	float TimeSinceCreation;
	
	// Virtual Methods
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	// Sets default values for this actor's properties
	AItemBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Control whether the Item should Float/Rotate
	UPROPERTY()
	bool bShouldAnimate;

	// Interact with Items in the world (E)
	UFUNCTION()
	virtual void OnInteract(class AHeroBase* Hero);

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
};
