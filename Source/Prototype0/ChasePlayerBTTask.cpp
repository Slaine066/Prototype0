// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayerBTTask.h"

#include "HeroBase.h"
#include "MobAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UChasePlayerBTTask::UChasePlayerBTTask()
{
	// Set Node Name
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayerBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AHeroBase* Hero = Cast<AHeroBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Move Request
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Hero);
	MoveRequest.SetAcceptanceRadius(40.f);

	FNavPathSharedPtr NavigationPath;
	AMobAIController* MobAIController = Cast<AMobAIController>(OwnerComp.GetAIOwner());
	
	MobAIController->MoveTo(MoveRequest, &NavigationPath);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	return EBTNodeResult::InProgress;
}