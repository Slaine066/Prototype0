// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TurnToPlayerBTTask.generated.h"

UCLASS()
class PROTOTYPE0_API UTurnToPlayerBTTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UTurnToPlayerBTTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
