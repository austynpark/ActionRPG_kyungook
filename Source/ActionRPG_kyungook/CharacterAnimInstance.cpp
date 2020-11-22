// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterAnimInstance.h"
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		// Gets the owner of this animation
		Pawn = TryGetPawnOwner();
		//Pawn = dynamic_cast<ACharacterBase*>(TryGetPawnOwner());
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	
	if (Pawn != nullptr)
	{
		FVector Speed = Pawn->GetVelocity();
		UE_LOG(LogTemp, Warning, TEXT("Speed.X : %f, Speed.y : %f"), Speed.X, Speed.Y);
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		Direction = LateralSpeed.Rotation().Yaw;
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		
		MovementSpeed = LateralSpeed.Size();

	}
	else
	{
		//Pawn = dynamic_cast<ACharacterBase*>(TryGetPawnOwner());
		Pawn = TryGetPawnOwner();
	}
}
