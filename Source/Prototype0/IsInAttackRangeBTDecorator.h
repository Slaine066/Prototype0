// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsInAttackRangeBTDecorator.generated.h"

UCLASS()
class PROTOTYPE0_API UIsInAttackRangeBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UIsInAttackRangeBTDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const override;
};
