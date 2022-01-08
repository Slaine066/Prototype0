// Fill out your copyright notice in the Description page of Project Settings.


#include "ShouldRetreatBTService.h"

#include "MobAIController.h"
#include "MobBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UShouldRetreatBTService::UShouldRetreatBTService()
{
	NodeName = "Should Retreat";
}

void UShouldRetreatBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AMobAIController* MobAIController = Cast<AMobAIController>(OwnerComp.GetAIOwner());
	const AMobBase* Mob = Cast<AMobBase>(MobAIController->GetPawn());

	const FVector DistanceFromInitialLocation = Mob->GetActorLocation() - MobAIController->InitialLocation;
	
	if (DistanceFromInitialLocation.Size() >= 1500.f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("Player", nullptr);
	}
}
