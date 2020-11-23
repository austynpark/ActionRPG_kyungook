// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	InterpSpeed = 5.0f;
	bIsInterping = false;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartPoint = GetActorLocation();
	EndPoint += StartPoint;
	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterp, 1.f);
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInterping)
	{
		CurrentPoint = GetActorLocation();
		SetActorLocation(FMath::VInterpTo(CurrentPoint, EndPoint, DeltaTime, InterpSpeed));
		UpdateFloatingPlatform();
	}
}

void AFloatingPlatform::UpdateFloatingPlatform()
{
	if (EndPoint == CurrentPoint)
	{
		ToggleInterp();
		EndPoint = StartPoint;
		StartPoint = CurrentPoint;
		GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterp, 1.f);
	}
}

