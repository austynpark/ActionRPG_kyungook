// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class ACTIONRPG_KYUNGOOK_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	UPROPERTY(Category = "Platform",VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Platform", EditAnywhere)
	FVector StartPoint;

	UPROPERTY(Category = "Platform", meta = (MakeEditWidget = "true"))
	FVector EndPoint;

	// Speed of Floating Platform
	UPROPERTY(Category = "Platform", EditAnywhere)
	float InterpSpeed;

	FVector CurrentPoint;

	FTimerHandle InterpTimer;

	bool bIsInterping;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Exchange Value of StartPoint <-> EndPoint if Platform reaches EndPoint
	void UpdateFloatingPlatform();
};
