// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBTTask.h"

#include "AIController.h"
#include "MobBase.h"

UAttackBTTask::UAttackBTTask()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMobBase* Mob = Cast<AMobBase>(OwnerComp.GetAIOwner()->GetCharacter());
	
	if (Mob)
	{
		Mob->Attack();
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	return EBTNodeResult::InProgress;
}

void UAttackBTTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);
	
	AMobBase* Mob = Cast<AMobBase>(OwnerComp.GetAIOwner()->GetCharacter());
	
	if (Mob && !Mob->bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}