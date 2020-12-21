// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"

#include "CharacterBase.h"

APotion::APotion()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

void APotion::BeginPlay()
{	
	Super::BeginPlay();
}

void APotion::OnUse_Implementation(ACharacterBase* Character)
{
	if (Character)
	{
		Character->Health += 10.f;
	}
	UE_LOG(LogTemp, Warning, TEXT("Potion On Use Called"));
	
}

void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Potion Tick"));
}

void APotion::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		ACharacterBase* Character = Cast<ACharacterBase>(OtherActor);
		if (Character)
		{
			Character->AddToInventory(this);
			this->SetActorHiddenInGame(true);
			this->SetActorEnableCollision(false);
		}
	}
}

void APotion::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
