// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindRandomLocationBTTask.generated.h"

UCLASS()
class PROTOTYPE0_API UFindRandomLocationBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (AllowPrivateAccess = "true"))
	float SearchRadius;

public:
	UFindRandomLocationBTTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};