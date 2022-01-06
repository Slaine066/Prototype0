// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"

#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Ews_Free		UMETA(DisplayName = "Free"),
	Ews_Equipped	UMETA(DisplayName = "Equipped"),
	Ews_Default		UMETA(DisplayName = "Default")
};

class ACharacterBase;

UCLASS()
class PROTOTYPE0_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

	/*
	** Private Properties
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	EWeaponState WeaponState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	ACharacterBase* WeaponOwner;
	
	// Damage dealt by this Weapon every Hit
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	// TODO: Disabled the error line, seems a problem of Unreal/Rider
	// ReSharper disable once UnrealHeaderToolParserError
	class UNiagaraSystem* HitParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundCue* HitSound;
	
	// Sound which is played after EquipWeapon()
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundCue* OnEquipWeaponSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Overlap Override Methods
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
public:
	// Sets default values for this actor's properties
	AWeaponBase();
	
	// Called every frame
    virtual void Tick(float DeltaTime) override;

	/*
	** Public Methods
	*/
	virtual void OnInteract(class AHeroBase* Hero) override; // OnOverlapBegin

	/*
	** Getters & Setters
	*/
	FORCEINLINE void SetWeaponState(const EWeaponState State) { WeaponState = State; }
	FORCEINLINE EWeaponState GetWeaponState() const { return WeaponState; }
	FORCEINLINE void SetWeaponOwner(ACharacterBase* WepOwner) { WeaponOwner = WepOwner; }
	FORCEINLINE ACharacterBase* GetWeaponOwner() const { return WeaponOwner; }
};
