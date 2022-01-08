// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ShouldRetreatBTService.generated.h"

UCLASS()
class PROTOTYPE0_API UShouldRetreatBTService : public UBTService
{
	GENERATED_BODY()

public:
	UShouldRetreatBTService();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
