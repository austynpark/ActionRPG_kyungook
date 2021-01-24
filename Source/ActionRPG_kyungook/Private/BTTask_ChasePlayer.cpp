// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

#include "EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{

	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComponent.GetAIOwner());
	
	AActor* Player = Cast<AActor>(OwnerComponent.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(AIController->PlayerKeyID));

	if (AIController)
	{
		AIController->MoveToActor(Player, 50.0f);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
