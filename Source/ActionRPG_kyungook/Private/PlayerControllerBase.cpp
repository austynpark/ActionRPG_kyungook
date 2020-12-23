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
	HUDInventory->SetVisibility(ESlateVisibility::Hidden);
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::I, EInputEvent::IE_Pressed, this, &APlayerControllerBase::ToggleInventoryHUD);

}

void APlayerControllerBase::ToggleInventoryHUD()
{
	if (HUDInventory->GetVisibility() == ESlateVisibility::Visible)
	{
		HUDInventory->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;
		UE_LOG(LogTemp, Warning, TEXT("Show Cursor = False"));
	}
	else
	{
		HUDInventory->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
		UE_LOG(LogTemp, Warning, TEXT("Show Cursor = True"));
	}
}
