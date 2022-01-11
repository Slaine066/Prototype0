// Fill out your copyright notice in the Description page of Project Settings.


#include "IsInAttackRangeBTDecorator.h"

#include <string>

#include "AIController.h"
#include "HeroBase.h"
#include "MobAIController.h"
#include "MobBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UIsInAttackRangeBTDecorator::UIsInAttackRangeBTDecorator()
{
	NodeName = "Is In Attack Range";
}

bool UIsInAttackRangeBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	const AMobAIController* MobAIController = Cast<AMobAIController>(OwnerComp.GetAIOwner());
	const AMobBase* Mob = Cast<AMobBase>(MobAIController->GetPawn());
	const AHeroBase* Hero = Cast<AHeroBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	
	const bool bResult = (Mob->GetDistanceTo(Hero) <= 200);
	return bResult;
}
