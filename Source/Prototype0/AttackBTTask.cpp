// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBTTask.h"

#include "AIController.h"
#include "HeroBase.h"
#include "MobAIController.h"
#include "MobBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UAttackBTTask::UAttackBTTask()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHeroBase* Hero = Cast<AHeroBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	if (!Hero) { return EBTNodeResult::Failed; }

	if (Hero->bIsDead)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("Player", nullptr);
		return EBTNodeResult::Succeeded;
	}
	
	const AMobAIController* MobAIController = Cast<AMobAIController>(OwnerComp.GetAIOwner());
	AMobBase* Mob = Cast<AMobBase>(MobAIController->GetCharacter());
	
	if (Mob)
	{
		Mob->Attack();
	}
	
	return EBTNodeResult::InProgress;
}

void UAttackBTTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);
	
	AMobBase* Mob = Cast<AMobBase>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Mob && !Mob->bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}