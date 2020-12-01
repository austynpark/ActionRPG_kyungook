// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class ACTIONRPG_KYUNGOOK_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Item", VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	/** Base shape Collision */
	UPROPERTY(Category = "Item | Collision", VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* Collider;

	UPROPERTY(Category = "Item | Item Rotation", EditAnywhere, BlueprintReadWrite)
	bool bIsRotate;

	/** Axis for Rotation */
	UPROPERTY(Category = "Item | Item Rotation", EditAnywhere, BlueprintReadWrite)
	FVector RotAxis;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
