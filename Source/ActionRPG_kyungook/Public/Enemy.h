// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UENUM()
enum class EEnemyMovementStatus : uint8
{
	EMS_IDLE UMETA(DisplayName = "Idle"),
	EMS_FOLLOW UMETA(DisplayName = "Follow"),
	EMS_ATTACK UMETA(DisplayName = "Attack"),

	EMS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class ACTIONRPG_KYUNGOOK_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "AI Behavior")
	class UBehaviorTree* BT_Asset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
