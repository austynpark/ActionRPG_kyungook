// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class ACTIONRPG_KYUNGOOK_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();
private:

	/** Overlap Volume for functionality to be triggered */
	UPROPERTY(Category = "Floor Switch", VisibleAnywhere, BlueprintReadOnly, meta= (AllowPrivateAccess = "true"))
	class UBoxComponent* Trigger;

	/** Switch Mesh for the Character to step on */
	UPROPERTY(Category = "Floor Switch", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FloorSwitch;

	/** Door Mesh which lifted when Switch is stepped on */
	UPROPERTY(Category = "Floor Switch", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Door;

	UPROPERTY(Category = "Floor Switch", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsTriggered;

	FTimerHandle SwitchHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Initial Location of the Door to be moved */
	UPROPERTY(Category = "Floor Switch", EditAnywhere, BlueprintReadWrite)
	FVector InitialDoorLocation;

	/** Initial Location of the Switch to be moved */
	UPROPERTY(Category = "Floor Switch", EditAnywhere, BlueprintReadWrite)
	FVector InitialSwitchLocation;

	/** Event Raise Door & Switch Z value*/
	UFUNCTION(Category = "Floor Switch", BlueprintImplementableEvent)
	void RaiseDoor();

	/** Event Lower Door & Switch Z value*/
	UFUNCTION(Category = "Floor Switch", BlueprintImplementableEvent)
	void LowerDoor();

	/** Update location of Door & Switch Z value */
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void UpdateLocation(float Door_Z, float Switch_Z);
};
