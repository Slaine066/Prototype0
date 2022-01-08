// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAIController.h"

#include "HeroBase.h"
#include "MobBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMobAIController::AMobAIController()
{
	// Initialize Behavior Tree and Blackboard
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	// Setup Perception Component
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	SetPerceptionComponent(*AIPerceptionComponent);

	// Setup Sight Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->PeripheralVisionAngleDegrees = 360.f;
	SightConfig->SightRadius = 800.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius * 2;
	SightConfig->SetMaxAge(0.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// Attach Sense Config to Perception Component
	GetAIPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetAIPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMobAIController::OnTargetPerceptionUpdate);
	GetAIPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AMobAIController::OnPossess(APawn * MobPawn)
{
	Super::OnPossess(MobPawn);
	
	// Get Reference to the Mob
	AMobBase* Mob = Cast<AMobBase>(MobPawn);
	InitialLocation = Mob->GetActorLocation();
	
	if (Mob)
	{
		if (Mob->GetBehaviorTree()->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(Mob->GetBehaviorTree()->BlackboardAsset));

			// Initialize Blackboard Values
			GetBlackboardComponent()->SetValueAsObject("Player", nullptr);
			GetBlackboardComponent()->SetValueAsBool("IsInAttackRange", false);
		}

		// Run Behavior Tree
		BehaviorTreeComponent->StartTree(*Mob->GetBehaviorTree());
	}
}

void AMobAIController::OnTargetPerceptionUpdate(AActor* Actor, const FAIStimulus Stimulus)
{
	AMobBase* Mob = Cast<AMobBase>(GetCharacter());
	if (Mob && !Mob->bIsDead)
	{
		AHeroBase* Hero = Cast<AHeroBase>(Actor);
		if (Hero)
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				UE_LOG(LogTemp, Warning, TEXT("Sensed. Mob Should Chase."));
				GetBlackboardComponent()->SetValueAsObject("Player", Hero);
			}
		}
	}
}