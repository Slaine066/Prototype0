// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MobAIController.generated.h"

UCLASS()
class PROTOTYPE0_API AMobAIController : public AAIController
{
	GENERATED_BODY()

	/*
	** Private Properties
	*/
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;

	/*
	** Private Methods
	*/
	UFUNCTION()
	virtual void OnPossess(APawn* MobPawn) override; 

	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
	
public:
	AMobAIController();
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	FVector InitialLocation;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return BehaviorTreeComponent; }
};
