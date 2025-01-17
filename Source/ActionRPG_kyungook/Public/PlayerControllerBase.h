// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_KYUNGOOK_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	/** Reference to the UMG asset in the editor */
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	/** Var to Hold the Widget after creation */
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite)
	UUserWidget* HUDOverlay;

	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HUDInventoryAsset;
	
	UPROPERTY(Category = "Widget", EditAnywhere, BlueprintReadWrite)
	UUserWidget* HUDInventory;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void ToggleInventoryHUD();
protected:
	virtual void BeginPlay() override;
};
