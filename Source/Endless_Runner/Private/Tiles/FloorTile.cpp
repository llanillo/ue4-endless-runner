// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/FloorTile.h"
#include "Collectables/CoinItem.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Player/PlayerBase.h"
#include "GameMode/EndlessRunnerGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Obstacles/WallObstacle.h"

// Sets default values
AFloorTile::AFloorTile()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;
	
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);

	LeftBlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBlockMesh"));
	LeftBlockMesh->SetupAttachment(SceneComponent);

	RightBlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBlockMesh"));
	RightBlockMesh->SetupAttachment(SceneComponent);
	
	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Point"));
	AttachPoint->SetupAttachment(SceneComponent);

	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Center Lane"));
	CenterLane->SetupAttachment(SceneComponent);

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Right Lane"));
	RightLane->SetupAttachment(SceneComponent);

	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Left Lane"));
	LeftLane->SetupAttachment(SceneComponent);

	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Floor Trigger Box"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.0f, 500.0f, 200.0f));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	MainGameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	check(MainGameMode);

	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnTriggerBoxOverlap);
}

const FTransform& AFloorTile::GetAttachmentTransform() const
{
	return AttachPoint->GetComponentTransform();
}

FVector AFloorTile::GetFloorBounds() const
{
	return FloorMesh->CalcBounds(FloorMesh->GetComponentTransform()).BoxExtent;
}

void AFloorTile::SpawnItems()
{
	if(IsValid(SmallObstacleClass) && IsValid(BigObstacleClass) && IsValid(CoinItemClass))
	{
		int32 NumBigWalls = 0;
		SpawnLaneItem(CenterLane, NumBigWalls);
		SpawnLaneItem(RightLane, NumBigWalls);
		SpawnLaneItem(LeftLane, NumBigWalls);
	}
}

void AFloorTile::SpawnLaneItem(const UArrowComponent* Lane, int32& NumBigWalls)
{
	const float RandValue = FMath::FRandRange(0.0f, 1.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if(UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent1, SpawnPercent2, true, true))
	{
		AWallObstacle* SmallWallObstacle = GetWorld()->SpawnActor<AWallObstacle>(SmallObstacleClass, Lane->GetComponentTransform(), SpawnParams);
		ChildActors.Add(SmallWallObstacle);
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent2, SpawnPercent3, true, true))
	{
		if(NumBigWalls <= 2)
		{
			AWallObstacle* BigWallObstacle = GetWorld()->SpawnActor<AWallObstacle>(BigObstacleClass, Lane->GetComponentTransform(), SpawnParams);

			if(BigWallObstacle)
			{
				NumBigWalls++;
			}
			
			ChildActors.Add(BigWallObstacle);
		}
		else
		{
			AWallObstacle* SmallWallObstacle = GetWorld()->SpawnActor<AWallObstacle>(SmallObstacleClass, Lane->GetComponentTransform(), SpawnParams);
			ChildActors.Add(SmallWallObstacle);
		}
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent3, 1.0f, true, true))
	{
		ACoinItem* CoinItem = GetWorld()->SpawnActor<ACoinItem>(CoinItemClass, Lane->GetComponentTransform(), SpawnParams);
		ChildActors.Add(CoinItem);
	}
}

void AFloorTile::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APlayerBase* MainCharacter = Cast<APlayerBase>(OtherActor);

	if (MainCharacter)
	{
		MainGameMode->AddFloorTile(true);
		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFloorTile::DestroyFloorTile, 2.0f, false);
	}
}

void AFloorTile::DestroyFloorTile()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	for(AActor* Actor : ChildActors)
	{
		if(IsValid(Actor))
		{
			Actor->Destroy();
		}
	}

	ChildActors.Empty();
	MainGameMode->RemoveTile(this);
	Destroy();
}
