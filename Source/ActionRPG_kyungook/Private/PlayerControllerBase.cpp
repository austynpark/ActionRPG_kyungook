// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "Blueprint/UserWidget.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	if (HUDInventoryAsset)
	{
		HUDInventory = CreateWidget<UUserWidget>(this, HUDInventoryAsset);
	}

	HUDOverlay->AddToViewport();
	HUDInventory->AddToViewport();

	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	HUDInventory->SetVisibility(ESlateVisibility::Visible);
}