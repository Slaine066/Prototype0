// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "CharacterController.h"
#include "HeroBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckHero();
}

void UCharacterAnimInstance::CheckHero()
{
	if (!Hero)
	{
		APawn* Pawn = TryGetPawnOwner();

		if (Pawn)
		{
			Hero = Cast<AHeroBase>(Pawn);
		}
	}
}

void UCharacterAnimInstance::UpdateSpeed()
{
	CheckHero();

	if (Hero)
	{
		const FVector Velocity = Hero->GetVelocity();
		const FVector LateralVelocity = FVector(Velocity.X, Velocity.Y, 0.f);

		Speed = LateralVelocity.Size();
	}
}

void UCharacterAnimInstance::PlayFootstepSound()
{
	CheckHero();
	
	if (Hero)
	{
		const FVector PawnLocationStart = Hero->GetActorLocation();
		const FVector PawnLocationEnd = PawnLocationStart - FVector(0.f, 0.f, 150.f);
	
		FHitResult HitResult;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, PawnLocationStart, PawnLocationEnd, ECollisionChannel::ECC_Visibility))
		{
			UGameplayStatics::PlaySoundAtLocation(this, FootstepSound, HitResult.Location);
		}
	}
}

void UCharacterAnimInstance::AttackCombo()
{
	CheckHero();

	if (Hero)
	{
		Hero->AttackCombo();
	}
}

void UCharacterAnimInstance::PlayAttackVoice()
{
	CheckHero();

	if (Hero)
	{
		switch (Hero->GetComboCounter())
		{
			case 1:
				UGameplayStatics::PlaySoundAtLocation(this, AttackVoice1, Hero->GetActorLocation());
				break;
			case 2:
				UGameplayStatics::PlaySoundAtLocation(this, AttackVoice2, Hero->GetActorLocation());
				break;
			case 0:
				UGameplayStatics::PlaySoundAtLocation(this, AttackVoice3, Hero->GetActorLocation());
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("UCharacterAnimInstance::PlayAttackSound(): Default"));
		}
	}
}

void UCharacterAnimInstance::Die()
{
	CheckHero();

	if (Hero)
	{
		Hero->GetMesh()->bPauseAnims = true;
		Hero->GetMesh()->bNoSkeletonUpdate = true;

		ACharacterController* CharacterController = Cast<ACharacterController>(Hero->GetController());
		Hero->DisableInput(CharacterController);
	}
}
