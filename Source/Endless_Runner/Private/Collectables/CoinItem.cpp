// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/CoinItem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ACoinItem::ACoinItem()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereComponent->SetupAttachment(SceneComponent);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapPawnOnly"));
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(SphereComponent);
	MeshComponent->SetCollisionProfileName(TEXT("OverlapPawnOnly"));

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovementComponent->RotationRate = FRotator(0, 180, 0);	
}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
	
}