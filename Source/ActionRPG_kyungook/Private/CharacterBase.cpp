// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterBase.h"

#include "Item.h"
#include "Weapon.h"
#include "InventorySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 450.f; // Camera follows at this distance
	SpringArm->bUsePawnControlRotation = true;  // Rotates SpringArm based on controller
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Inventory = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("Inventory"));

	GetCapsuleComponent()->SetCapsuleSize(88.0f, 35.0f);

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Don't Rotate when the controller rotates.
	// Only Camera Rotates
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Uncomment this to move character in the direction of camera
	// Configure Character Movement
	// This should be true when if Battle Mode is ON
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Rotate Character and moves in the direction of input
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	MaxHealth = 100;
	Health = 100;
	MaxStamina = 100;
	Stamina = 100;
	LowStamina = 30;
	StaminaRate = 1;

	bIsShiftPressed = false;
	bIsJumping = false;

	MovementStatus = EMovementStatus::MS_Walk;
	StaminaStatus = EStaminaStatus::SS_Recovering;

	RightHandWeapon = nullptr;
	AttackCount = 0;
	bIsAttacking = false;
	bSaveAttack = false;

	AIStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStimuliSource"));
	AIStimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
}

void ACharacterBase::UseItem(AItem* item)
{
	if (item)
	{
		item->OnUse(this);
		Inventory->RemoveItem(item);
	}
}

void ACharacterBase::RemoveFromInventory(AItem* item)
{
	if (item)
	{
		Inventory->RemoveItem(item);
		item->SetActorHiddenInGame(false);
		item->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 50);
		item->SetActorEnableCollision(true);
	}
}

void ACharacterBase::SetRightHandWeapon(AWeapon* rightHandWeapon)
{
	if (RightHandWeapon != nullptr)
	{
		RightHandWeapon->Destroy();
	}

	RightHandWeapon = rightHandWeapon;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleStamina(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);

	// Rotates Controller's Foward Vector to direction of Camera looking
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &ACharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacterBase::LookUpRate);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACharacterBase::TurnOnRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACharacterBase::TurnOffRun);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterBase::LeftMouseButtonPressed);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ACharacterBase::LeftMouseButtonReleased);
}

void ACharacterBase::Jump()
{
	Super::Jump();
	bIsJumping = true;
	GetCharacterMovement()->GravityScale = 2.f;
}

void ACharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	bIsJumping = false;
	GetCharacterMovement()->GravityScale = 1.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACharacterBase::Falling()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACharacterBase::MoveForward(float value)
{
	if ((GetController() != nullptr) && (value != 0))
	{
		// Get Controller Yaw only takes X direction to move foward
		const FRotator ControlRotation(0, GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ACharacterBase::MoveRight(float value)
{
	if ((GetController() != nullptr) && (value != 0))
	{
		// Get Controller Yaw only takes Y direction to move side
		const FRotator ControlRotation(0, GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void ACharacterBase::LeftMouseButtonPressed()
{
	if (RightHandWeapon)
	{
		if(!bIsAttacking)
		{
			Attack();
		}
		else
		{
			bSaveAttack = true;
		}
	}
}

void ACharacterBase::LeftMouseButtonReleased()
{
}

void ACharacterBase::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACharacterBase::LookUpRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACharacterBase::TurnOnRun()
{
	bIsShiftPressed = true;
}

void ACharacterBase::TurnOffRun()
{
	bIsShiftPressed = false;
	GetWorldTimerManager().SetTimer(StaminaTimer, FTimerDelegate::CreateUObject(this, &ACharacterBase::SetStaminaStatus, EStaminaStatus::SS_Recovering), 0.5f, false);
}

void ACharacterBase::Attack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (CombatMontage && AnimInstance)
	{
		Stamina -= 50.f; 

		bIsAttacking = true;
		AnimInstance->Montage_Play(CombatMontage, 1.35f);
		FString sectionName = "Attack_" + FString::FromInt(AttackCount);
		AnimInstance->Montage_JumpToSection(FName(*sectionName), CombatMontage);
	}
}

void ACharacterBase::ComboEnd()
{
	AttackCount = 0;
	bSaveAttack = false;
	bIsAttacking = false;
}

void ACharacterBase::SaveAttack()
{	
	if (bSaveAttack)
	{
		bSaveAttack = false;
		++AttackCount;
		Attack();
	}
}

void ACharacterBase::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;

	switch (MovementStatus)
	{
	case EMovementStatus::MS_Walk:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;
	case EMovementStatus::MS_Run:
		GetCharacterMovement()->MaxWalkSpeed = 450.f;
		break;
	}
}

void ACharacterBase::HandleStamina(float val)
{
	switch(StaminaStatus)
	{
	case EStaminaStatus::SS_LowStamina:
	case EStaminaStatus::SS_Normal :
		if (bIsShiftPressed 
			&& (!FMath::IsNearlyZero(Stamina) && (Stamina > 0)))
		{
			SetMovementStatus(EMovementStatus::MS_Run);
			Stamina -= val * 5.f;

			if (Stamina <= LowStamina)
				SetStaminaStatus(EStaminaStatus::SS_LowStamina);
		}
		else
		{
			SetMovementStatus(EMovementStatus::MS_Walk);
			if (FMath::IsNearlyZero(Stamina))
			{
				SetStaminaStatus(EStaminaStatus::SS_Exhausted);
			}
		}
		break;
	case EStaminaStatus::SS_Exhausted :
		SetMovementStatus(EMovementStatus::MS_Walk);
		break;
	case EStaminaStatus::SS_Recovering :
		if (!bIsShiftPressed && (Stamina < MaxStamina))
			Stamina += val * StaminaRate;
		else
			SetStaminaStatus(EStaminaStatus::SS_Normal);
		break;
		
	}
}

void ACharacterBase::AddToInventory(AItem* item)
{
	if (item)
	{
		Inventory->AddItem(item);
	}
}
