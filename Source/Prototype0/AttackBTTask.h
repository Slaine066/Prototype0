// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackBTTask.generated.h"

class AMobBase;

UCLASS()
class PROTOTYPE0_API UAttackBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UAttackBTTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;
};