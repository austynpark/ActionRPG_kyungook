// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"

#include "Critter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint()const
{
	return UKismetMathLibrary::RandomPointInBoundingBox(
		SpawnBox->GetComponentLocation(),
		SpawnBox->GetScaledBoxExtent()
	);
}

void ASpawnVolume::SpawnPawn_Implementation(UClass* _ToSpawn, const FVector& Location)
{
	if (_ToSpawn)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			//Spawn Actor returns spawned object address
			ACritter* SpawnedActor = 
			World->SpawnActor<ACritter>(_ToSpawn, Location, FRotator(0.f));
		}

		
	}
}

