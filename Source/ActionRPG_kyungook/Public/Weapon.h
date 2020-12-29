// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_KYUNGOOK_API AWeapon : public AItem
{
	GENERATED_BODY()
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class USoundCue* UseSound;
public:
	AWeapon();

	UPROPERTY(Category = "SkeletalMesh", VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMesh;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void OnUse_Implementation(class ACharacterBase* Character);

};
