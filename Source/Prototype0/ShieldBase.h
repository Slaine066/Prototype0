// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ShieldBase.generated.h"

UENUM(BlueprintType)
enum class EShieldState : uint8
{
	Ess_Free		UMETA(DisplayName = "Free"),
	Ess_Equipped	UMETA(DisplayName = "Equipped"),
	Ess_Default		UMETA(DisplayName = "Default")
};

UCLASS()
class PROTOTYPE0_API AShieldBase : public AItemBase
{
	GENERATED_BODY()

	/*
	** Private Properties
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	EShieldState ShieldState;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Defense;
	
	// Sound which is played after EquipShield()
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundCue* OnEquipShieldSound;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap Override Methods
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
public:
	// Sets default values for this actor's properties
	AShieldBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	** Public Methods
	*/
	virtual void OnInteract(class AHeroBase* Hero) override; // Equip Shield upon OverlapBegin

	/*
	** Getters & Setters
	*/
	FORCEINLINE void SetShieldState(const EShieldState State) { ShieldState = State; }
	FORCEINLINE EShieldState GetShieldState() const { return ShieldState; }
};
