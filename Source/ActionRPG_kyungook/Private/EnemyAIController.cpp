// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Enemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AEnemyAIController::AEnemyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BehaviorComponent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	
	AIperception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	
	AIConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSight"));
	
	if (AIperception)
	{
		SetPerceptionComponent(*AIperception);

		AIConfigSight->SightRadius = 3000.0f;
		AIConfigSight->LoseSightRadius = 3500.0f;
		AIConfigSight->PeripheralVisionAngleDegrees = 45.0f;

		AIConfigSight->DetectionByAffiliation.bDetectEnemies = true;
		AIConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
		AIConfigSight->DetectionByAffiliation.bDetectNeutrals = true;

		AIperception->ConfigureSense(*AIConfigSight);
		AIperception->SetDominantSense(AIConfigSight->GetSenseImplementation());
	}

	
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemy* Enemy = Cast<AEnemy>(InPawn);

	if(Enemy && Enemy->BT_Asset)
	{
		BlackboardComp->InitializeBlackboard(*Enemy->BT_Asset->BlackboardAsset);

		PlayerKeyID = BlackboardComp->GetKeyID("TargetActor");

		BehaviorTreeComp->StartTree(*Enemy->BT_Asset);
	}
	
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	AIperception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetSensed);
}

void AEnemyAIController::OnTargetSensed(AActor* Actor, FAIStimulus Stimulus)
{
	BlackboardComp->SetValueAsObject("TargetActor", Actor);
}