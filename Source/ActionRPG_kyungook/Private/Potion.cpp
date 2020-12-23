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
}

void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APotion::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
}

void APotion::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
