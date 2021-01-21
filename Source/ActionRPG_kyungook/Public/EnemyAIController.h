// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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

	//UPROPERTY(Transient)
	//class UBlackboardComponent* BlackboardComp;

	//UPROPERTY(Transient)
	//class UBehaviorTreeComponent* BehaviorTreeComp;
	//
	UPROPERTY(Category = "Behavior Tree",BlueprintReadOnly,EditAnywhere,meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* BT_Asset;
public:

	AEnemyAIController();
	//
	//class UAIPerceptionComponent* AIperception;
	//class UAISenseConfig_Sight* AIConfigSight;
};
