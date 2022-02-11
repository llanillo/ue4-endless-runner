// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/WallObstacle.h"
#include "Player/PlayerBase.h"

// Sets default values
AWallObstacle::AWallObstacle()
{
 	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(SceneComponent);
}

void AWallObstacle::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentHit.AddDynamic(this, &AWallObstacle::OnObstacleHit);
}

void AWallObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                  FVector NormalImpulse, const FHitResult& Hit)
{
	APlayerBase* Player = Cast<APlayerBase>(OtherActor);
	
	if(Player)
	{
		Player->Death();
	}
}
