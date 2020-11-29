// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class ACTIONRPG_KYUNGOOK_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(Category = "Spawn", VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* SpawnBox;

	UPROPERTY(Category = "Spawn", EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ACritter> ToSpawn; // Pawn To Spawn

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get Random Point In Spawn Box
	UFUNCTION(Category = "Spawn", BlueprintPure)
	FVector GetSpawnPoint() const; 

	// Spawn Critter(Pawn) at the Location
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spawn")
	void SpawnPawn(UClass* _ToSpawn, const FVector& Location);
	virtual void SpawnPawn_Implementation(UClass* _ToSpawn, const FVector& Location);
};
