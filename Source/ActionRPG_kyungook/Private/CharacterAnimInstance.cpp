// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterAnimInstance.h"
#include "CharacterBase.h"
#include "Engine/GameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		// Gets the owner of this animation
		Pawn = Cast<ACharacterBase>(TryGetPawnOwner());
		bIsMoving = false;
		//Pawn = dynamic_cast<ACharacterBase*>(TryGetPawnOwner());
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	
	if (Pawn != nullptr)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		Direction = LateralSpeed.Rotation().Yaw;
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		
		MovementSpeed = LateralSpeed.Size();

		bIsMoving = ((MovementSpeed == 0) && !bIsInAir) ? false : true;
	}
	else
	{
		Pawn = Cast<ACharacterBase>(TryGetPawnOwner());
	}
}
