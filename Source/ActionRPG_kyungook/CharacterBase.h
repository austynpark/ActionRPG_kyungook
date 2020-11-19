// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class ACTIONRPG_KYUNGOOK_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
private:
	/** SpringArm poistioning the camera behind the player */
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	/** Camera following behind the player */
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	ACharacterBase();

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return Camera; }

	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly)
	float BaseTurnRate = 65.f;
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly)
	float BaseLookUpRate = 65.f;

	UPROPERTY(Category = "Movement Speed", EditAnywhere, BlueprintReadOnly)
	float JumpSpeed = 800.f;
	UPROPERTY(Category = "Movement Speed", EditAnywhere, BlueprintReadOnly)
	float WalkSpeed = 150.f;


	bool bIsJumping;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
	
	virtual void Landed(const FHitResult& Hit) override;

	virtual void Falling() override;

	void MoveForward(float value);
	
	void MoveRight(float value);
	
	/** Called via input to turn at a given rate
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpRate(float Rate);

	/** Called if any shift keys are pressed, increase Max walk speed = 300*/
	void TurnOnRun();
	/** Called if any shift keys are released, decend Max walk speed = 450*/
	void TurnOffRun();
};
