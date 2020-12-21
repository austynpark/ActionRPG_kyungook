// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = Collider;

	ItemParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Item Particle"));
	ItemParticle->SetupAttachment(GetRootComponent());

	bIsRotate = false;

	ItemName = FText::FromString("ItemName");
	ItemDescription = FText::FromString("ItemDescription");
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsRotate)
	{
		AddActorLocalRotation(FQuat(RotAxis, DeltaTime));
	}
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, OverlapParticle, GetActorLocation(), FRotator(0), true);
	UGameplayStatics::PlaySound2D(this, OverlapSound);
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AItem::OnUse_Implementation(ACharacterBase* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Base Class On Use Func Called"));
}

