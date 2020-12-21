// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	MS_Walk UMETA(DisplayName = "Walking"),
	MS_Run UMETA(DisplayName = "Running"),

	// Make sure enum var to keep under the MAX value.
	MS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	SS_Normal UMETA(DisplayName = "Normal"),
	SS_LowStamina UMETA(DisplayName = "LowStamina"),
	SS_Recovering UMETA(DisplayName = "Recovering"),
	SS_Exhausted UMETA(DisplayName = "Exhausted"),

	SS_MAX UMETA(DisplayName = "MAX"),
};

UCLASS()
class ACTIONRPG_KYUNGOOK_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
private:
	/** SpringArm positioning the camera behind the player */
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera following behind the player */
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Character Inventory */
	UPROPERTY(Category = "Inventory", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventorySystemComponent* Inventory;

	UPROPERTY(Category = "Enums", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMovementStatus MovementStatus;

	UPROPERTY(Category = "Enums", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EStaminaStatus StaminaStatus;

public:
	// Sets default values for this character's properties
	ACharacterBase();

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return Camera; }
	FORCEINLINE EMovementStatus GetMovementStatus() const { return MovementStatus;}
	FORCEINLINE EStaminaStatus GetStaminaStatus() const { return StaminaStatus; }

	/** Set a MovmentStatus of Character and Speed */
	void SetMovementStatus(EMovementStatus Status);
	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly)
	float BaseTurnRate = 65.f;
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly)
	float BaseLookUpRate = 65.f;

	UPROPERTY(Category = "Movement Speed", EditAnywhere, BlueprintReadOnly)
	float JumpSpeed = 800.f;
	UPROPERTY(Category = "Movement Speed", EditAnywhere, BlueprintReadOnly)
	float WalkSpeed = 150.f;

	bool bIsShiftPressed;

	bool bIsJumping;

	/** Player Stats
	* @param 
	*/
	FTimerHandle StaminaTimer;

	UPROPERTY(Category = "Player Stats", EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(Category = "Player Stats", EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(Category = "Player Stats", EditDefaultsOnly, BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(Category = "Player Stats", EditAnywhere, BlueprintReadWrite)
	float Stamina;

	float LowStamina;

	/**  Rate of Stamina Recover & Use */
	UPROPERTY(Category = "Player Stats", EditDefaultsOnly, BlueprintReadWrite)
	float StaminaRate;

	/** 
	* Item Use
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	void UseItem(class AItem* item);

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

	/** if(Stamina Status) 
	*	Normal -> val == 0 or Negative, 
	*	Recovering -> val > 0
	*	Exhausted -> MovmentSataus == Walk	
	*/
	void HandleStamina(float val);

	void AddToInventory(class AItem* item);
};
