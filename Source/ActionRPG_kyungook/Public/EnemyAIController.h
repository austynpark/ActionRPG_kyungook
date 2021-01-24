// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"

#include "EnemyAIController.generated.h"
/**
 * 
 */
UCLASS()
class ACTIONRPG_KYUNGOOK_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UFUNCTION()
	virtual void OnTargetSensed(AActor* Actor, FAIStimulus Stimulus);

public:

	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;

	uint8 PlayerKeyID;
	
	class UAIPerceptionComponent* AIperception;
	class UAISenseConfig_Sight* AIConfigSight;
};
