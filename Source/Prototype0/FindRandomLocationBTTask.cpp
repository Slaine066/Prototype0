// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocationBTTask.h"

#include "MobAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindRandomLocationBTTask::UFindRandomLocationBTTask()
{
	// Set Node Name
	NodeName = TEXT("Find Random Location");

	// Initialize Radius 
	SearchRadius = 500.f;
}

EBTNodeResult::Type UFindRandomLocationBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	const AMobAIController* MobAIController = Cast<AMobAIController>(OwnerComp.GetAIOwner());
	
	const FVector InitialLocation = MobAIController->InitialLocation;
	OUT FNavLocation Destination;
	
	if (NavigationSystem->GetRandomPointInNavigableRadius(InitialLocation, SearchRadius, Destination, nullptr))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("DestinationLocation", Destination.Location);
	}

	// Finish Task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}