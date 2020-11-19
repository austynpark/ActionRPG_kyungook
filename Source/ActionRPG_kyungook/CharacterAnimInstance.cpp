// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"


void UCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		// Gets the owner of this animation
		Pawn = TryGetPawnOwner();
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	else
	{
		FVector Speed = Pawn->GetVelocity();
		Direction = Pawn->GetActorRotation().Yaw;
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);	
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		MovementSpeed = LateralSpeed.Size();
		/*UE_LOG(LogTemp, Warning, TEXT("MovementSpeed : %f"), MovementSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Direction : %f"), Direction);*/
		//if (FMath::IsNearlyZero(Speed.Y)) // If its velocity of Y is nearly Zero, Pawn is moving forward
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Moving Foward"));
		//	bIsMovingSide = false;
		//	MovementSpeed = LateralSpeed.Size();
		//}
		//else // Pawn is moving toward to left or right
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Moving Left Right"));
		//	bIsMovingSide = true;
		//	SideMovementSpeed = LateralSpeed.Size();
		//}
	}
}
