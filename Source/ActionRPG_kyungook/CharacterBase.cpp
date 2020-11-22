// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


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

	GetCapsuleComponent()->SetCapsuleSize(88.0f, 35.0f);

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Don't Rotate when the controller rotates.
	// Only Camera Rotates
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bIsJumping = false;

	// Uncomment this to move character in the direction of camera
	// Configure Character Movement
	// This should be true when if Battle Mode is ON
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Rotate Character and moves in the direction of input
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

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
	UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
}

void ACharacterBase::TurnOffRun()
{
	UE_LOG(LogTemp, Warning, TEXT("Released"));
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

