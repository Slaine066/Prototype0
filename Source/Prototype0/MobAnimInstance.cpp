// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAnimInstance.h"

#include "MobBase.h"

void UMobAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CheckMob();
}

void UMobAnimInstance::CheckMob()
{
	if (!Mob)
	{
		APawn* Pawn = TryGetPawnOwner();

		if (Pawn)
		{
			Mob = Cast<AMobBase>(Pawn);
		}
	}
}

void UMobAnimInstance::UpdateSpeed()
{
	CheckMob();

	if (Mob)
	{
		const FVector Velocity = Mob->GetVelocity();
		const FVector LateralVelocity = FVector(Velocity.X, Velocity.Y, 0.f);

		Speed = LateralVelocity.Size();
	}
}

void UMobAnimInstance::Die()
{
	CheckMob();

	if (Mob)
	{
		Mob->GetMesh()->bPauseAnims = true;
		Mob->GetMesh()->bNoSkeletonUpdate = true;
	}
}
