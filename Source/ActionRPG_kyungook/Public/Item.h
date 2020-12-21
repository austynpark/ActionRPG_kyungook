// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)
class ACTIONRPG_KYUNGOOK_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Base shape Collision */
	UPROPERTY(Category = "Item | Collision", VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* Collider;

	/** Particle for Item */
	UPROPERTY(Category = "Item | Particle", VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* ItemParticle;

	/** Particle for Item Overlap */
	UPROPERTY(Category = "Item | Particle", EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* OverlapParticle;

	/** Sound for Item Overlap */
	UPROPERTY(Category = "Item | Sound", EditAnywhere, BlueprintReadOnly)
	class USoundCue* OverlapSound;

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

	/** Icon to display */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	//FSlateBrush ItemIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	UTexture2D* Thumbnail;

	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	/** User-visible long description */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	//UPROPERTY()
	//class UInventorySystemComponent* OwningInventory;

	//virtual void OnUse(class ACharacterBase* Character) PURE_VIRTUAL(AItem, );

	UFUNCTION(BlueprintNativeEvent)
	void OnUse(class ACharacterBase* Character);
	virtual void OnUse_Implementation(class ACharacterBase* Character);
};
