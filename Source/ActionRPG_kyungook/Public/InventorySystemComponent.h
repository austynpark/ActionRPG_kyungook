// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_KYUNGOOK_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<class AItem*> Items;
public:	
	// Sets default values for this component's properties
	UInventorySystemComponent();

	bool AddItem(class AItem* item);
	bool RemoveItem(class AItem* item);

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 0), Category = "Inventory")
	int32 capacity;

	/** Dynamic Delgate for UI Update*/
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
