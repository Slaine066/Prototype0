// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroBase.h"

#include "DamageIndicatorComponent.h"
#include "ItemBase.h"
#include "ShieldBase.h"
#include "WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AHeroBase::AHeroBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Spring Arm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	GetSpringArmComponent()->SetupAttachment(GetRootComponent());
	GetSpringArmComponent()->TargetArmLength = 500.f;
	GetSpringArmComponent()->TargetOffset = FVector(0.f, 0.f, 100.f);
	GetSpringArmComponent()->bUsePawnControlRotation = true;

	// Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	GetCameraComponent()->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	GetCameraComponent()->bUsePawnControlRotation = false;

	// Character
	// Doesn't rotate when Camera rotates.
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Movement
	// Moves in the direction of the input at "RotationRate" speed.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 650.f;
	
	StimuliComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimuli Component"));
	StimuliComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
	StimuliComponent->RegisterWithPerceptionSystem();
}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Combat Properties
	SetComboCounter(0);
	SetIsComboActive(false);

	// Setup Collision Profile
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PawnHero"));

	// Setup Weapon
	if (GetWeaponClass())
	{
		SetWeaponEquipped(GetWorld()->SpawnActor<AWeaponBase>(GetWeaponClass()), this);
	
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("Hand_RSocket");
		if (WeaponSocket)
		{
			WeaponSocket->AttachActor(GetWeaponEquipped(), GetMesh());
			GetWeaponEquipped()->GetMeshComponent()->SetCollisionProfileName(TEXT("WeaponHero"));
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
void AHeroBase::Tick(const float DeltaTime)
{
	if (!bIsDead)
	{
		Super::Tick(DeltaTime);
	}
}

// Called to bind functionality to input
void AHeroBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// Bindings
	PlayerInputComponent->BindAxis(TEXT("MoveStraight"), this, &AHeroBase::MoveStraight);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &AHeroBase::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("LookVertical"), this, &AHeroBase::LookVertical);
	PlayerInputComponent->BindAxis(TEXT("LookHorizontal"), this, &AHeroBase::LookHorizontal);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AHeroBase::Interact);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AHeroBase::Attack);
}

// Move Forward (W) - Move Backward (S)
void AHeroBase::MoveStraight(const float AxisValue)
{
	if (GetController() && AxisValue != 0.0f && !bIsAttacking)
	{
		// Get Controller Yaw Rotation
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get Forward Vector Direction from Controller Yaw Rotation
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		AddMovementInput(Direction, AxisValue);
	}
}

// Move Left (A) - Move Right (D)
void AHeroBase::MoveSide(const float AxisValue)
{
	if (GetController() && AxisValue != 0.0f && !bIsAttacking)
	{
		// Get Controller Yaw Rotation
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get Right Vector Direction from Controller Yaw Rotation
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Direction, AxisValue);
	}
}

// Look Vertical (Mouse UP/DOWN)
void AHeroBase::LookVertical(const float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

// Look Horizontal (Mouse LEFT/RIGHT)
void AHeroBase::LookHorizontal(const float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

// Interact with Items in the world (E)
void AHeroBase::Interact()
{
	AItemBase* Item = GetOverlappingItem();
	if (Item)
	{
		Item->OnInteract(this);
	}
}

// Attack (Mouse Left Click)
void AHeroBase::Attack()
{
	if (GetWeaponEquipped())
	{
		if (bIsAttacking)
		{
			if (GetComboCounter() != 0)
			{
				SetIsComboActive(true);
			}
		}
		else
		{
			bIsAttacking = true;
			SetComboCounter(1);
			PlayAnimMontage(AttackMontages[0]);
		}
	}
}

void AHeroBase::AttackCombo()
{
	if (GetWeaponEquipped())
	{
		if (GetIsComboActive())
		{
			SetIsComboActive(false);
			
			switch(GetComboCounter())
			{
			case 1:
				SetComboCounter(2);
				PlayAnimMontage(AttackMontages[1]);
				break;
			case 2:
				SetComboCounter(0);
				PlayAnimMontage(AttackMontages[2]);
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::AttackCombo(): Default"));
			}
		}
		else
		{
			bIsAttacking = false;
			SetComboCounter(0);
		}
	}
}

void AHeroBase::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
                              AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Takes Damage"));
	Super::OnDamageTaken(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}

void AHeroBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Dies"));
	Super::Die();
}