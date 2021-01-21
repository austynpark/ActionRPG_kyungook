// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AEnemyAIController::AEnemyAIController()
{
	//BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BehaviorComponent"));
	//BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	//
	//AIperception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	//AIConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSight"));
	//
	//if (AIperception)
	//{
	//	AIConfigSight->SightRadius = 3000.0f;
	//	AIConfigSight->LoseSightRadius = 3500.0f;
	//	AIConfigSight->PeripheralVisionAngleDegrees = 45.0f;

	//	AIConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	//	AIConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
	//	AIConfigSight->DetectionByAffiliation.bDetectNeutrals = true;

	//	AIperception->ConfigureSense(*AIConfigSight);
	//	AIperception->SetDominantSense(AIConfigSight->GetSenseImplementation());
	//}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BT_Asset)
	{
		RunBehaviorTree(BT_Asset);
	}
}

