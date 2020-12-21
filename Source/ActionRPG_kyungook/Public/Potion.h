// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_KYUNGOOK_API APotion : public AItem
{
	GENERATED_BODY()

	APotion();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item | Pickup Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;

	virtual void OnUse_Implementation(class ACharacterBase* Character) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
