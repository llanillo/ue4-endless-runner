#include "Tiles/ObstacleTile.h"
#include "Collectables/CoinItem.h"
#include "Components/ArrowComponent.h"
#include "Utility/Util.h"
#include "Obstacles/Obstacle.h"

AObstacleTile::AObstacleTile() : AFloorTile()
{
	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Center Lane"));
	CenterLane->SetupAttachment(GetSceneComponent());

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Right Lane"));
	RightLane->SetupAttachment(GetSceneComponent());
	
	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Left Lane"));
	LeftLane->SetupAttachment(GetSceneComponent());
}

void AObstacleTile::BeginPlay()
{
	Super::BeginPlay();

	GetFloorRoadMesh()->SetStaticMesh(Util::GetRandomStaticMesh(FloorMeshes));
	GetFloorRoadMesh()->SetWorldScale3D(FVector{30, 30, 30});
}

void AObstacleTile::SpawnItems()
{
	if(IsValid(SmallObstacleClass) && IsValid(BigObstacleClass) && IsValid(GetCoinItemClass()))
	{
		int32 NumBigWalls = 0;
		SpawnLaneItem(CenterLane, NumBigWalls);
		SpawnLaneItem(RightLane, NumBigWalls);
		SpawnLaneItem(LeftLane, NumBigWalls);
	}
}

void AObstacleTile::SpawnLaneItem(const UArrowComponent* Lane, int32& NumBigWalls)
{
	const float RandValue = FMath::FRandRange(0.0f, 1.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if(RandValue <= SpawnPercent1)
	{
		AObstacle* SmallObstacle = GetWorld()->SpawnActor<AObstacle>(SmallObstacleClass, Lane->GetComponentTransform(), SpawnParams);
		AddChildActor(SmallObstacle);
	}
	else if(RandValue <= SpawnPercent2)
	{
		if(NumBigWalls <= 1)
		{
			AObstacle* BigObstacle = GetWorld()->SpawnActor<AObstacle>(BigObstacleClass, Lane->GetComponentTransform(), SpawnParams);
			NumBigWalls++;
			AddChildActor(BigObstacle);
		}
		else
		{
			AObstacle* SmallObstacle = GetWorld()->SpawnActor<AObstacle>(SmallObstacleClass, Lane->GetComponentTransform(), SpawnParams);
			AddChildActor(SmallObstacle);
		}
	}
	else if(RandValue <= SpawnPercent3)
	{
		ACoinItem* CoinItem = GetWorld()->SpawnActor<ACoinItem>(GetCoinItemClass(), Lane->GetComponentTransform(), SpawnParams);
		AddChildActor(CoinItem);
	}
}