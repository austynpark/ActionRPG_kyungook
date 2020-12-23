// Fill out your copyright notice in the Description page of Project Settings.
#include "InventorySystemComponent.h"

#include "Item.h"
// Sets default values for this component's properties
UInventorySystemComponent::UInventorySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	capacity = 10;
}

// Called when the game starts
void UInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	Items.Reserve(capacity);
}

bool UInventorySystemComponent::AddItem(AItem* item)
{
	if (item && (Items.Num() < capacity))
	{
		Items.Add(item);
		if (OnInventoryUpdated.IsBound())
		{
			// Update UI
			OnInventoryUpdated.Broadcast();
		}

		return true;
	}

	return false;
}

bool UInventorySystemComponent::RemoveItem(AItem* item)
{
	if (item)
	{
		if (Items.Contains(item))
		{
			Items.RemoveSingle(item);
			if (OnInventoryUpdated.IsBound())
			{
				// Update UI
				OnInventoryUpdated.Broadcast();
			}
			return true;
		}
	}
	return false;
}

void UInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//for (auto& item : Items)
	//{
	//	if (Items[0] == nullptr)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Potion NULL"));
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Potion NOT DELETED"));
	//		UE_LOG(LogTemp, Warning, TEXT("%s"), *Items[0]->ItemName.ToString());
	//	}
	//}
	//
		
	// ...
}

