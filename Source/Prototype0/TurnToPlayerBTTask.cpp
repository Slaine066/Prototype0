// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnToPlayerBTTask.h"

#include "AIController.h"
#include "HeroBase.h"
#include "MobBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UTurnToPlayerBTTask::UTurnToPlayerBTTask()
{
	NodeName = TEXT("Turn To Player");
}

EBTNodeResult::Type UTurnToPlayerBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMobBase* Mob = Cast<AMobBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Mob) { return EBTNodeResult::Failed; }
	
	AHeroBase* Hero = Cast<AHeroBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	if (!Hero) { return EBTNodeResult::Failed; }
	
	FVector LookVector = Hero->GetActorLocation() - Mob->GetActorLocation();
	LookVector.Z = 0.0f;

	const FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Mob->SetActorRotation(FMath::RInterpTo(Mob->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.0f));

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
