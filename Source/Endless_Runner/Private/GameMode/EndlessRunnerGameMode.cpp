#include "GameMode/EndlessRunnerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/ArrowComponent.h"
#include "Tiles/FloorTile.h"
#include "Tiles/ObstacleTile.h"
#include "Environment/Pool/ObjectPool.h"
#include "UI/GameHud.h"

void AEndlessRunnerGameMode::BeginPlay()
{
	// Show player cursor at the start of the game
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	// Create and initialize the GUI
	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud);
	GameHud->InitializeHud(this);
	GameHud->AddToViewport();

	// Initial player lives
	CurrentLives = MaxLives;

	// Initialize the tiles pool and spawn the initial floor tiles
	const FVector InitialPosition = FVector{-10000, -10000, -10000};
	// TilesPool->InitializePool(FTransform{InitialPosition});
	CreateInitialFloorTiles(NumInitialFloorTiles);
}

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// Creates and attach the pool object component
	// TilesPool = CreateDefaultSubobject<UObjectPool>(TEXT("Floor Tiles Pool"));
	// AddOwnedComponent(TilesPool);
}
/*
 *	Spawn Initial Floor Tiles
 */
void AEndlessRunnerGameMode::CreateInitialFloorTiles(int InitialFloorTiles)
{
	// Lane switch values to control the player movement between lanes
	if (const AObstacleTile* Tile = AddFloorTile(false))
	{
		LaneSwitchValues.Add(Tile->GetLeftLane()->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->GetCenterLane()->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->GetRightLane()->GetComponentLocation().Y);
	}

	AddFloorTile(false);
	
	for (int i = 0; i < InitialFloorTiles; i++) 
	{
		AddFloorTile(true); 
	}
}

void AEndlessRunnerGameMode::RemoveTile(AFloorTile* Tile)
{
	FloorTileArray.Remove(Tile);
}

/*
 *	Spawn a floor tile in the next spawn point and move it to the next location
 */
AObstacleTile* AEndlessRunnerGameMode::AddFloorTile(bool SpawnItems)
{
	UWorld* World = GetWorld();
	
	if (World)
	{
		// AObstacleTile* Tile = Cast<AObstacleTile>(TilesPool->SpawnPooledObject(NextSpawnPoint));
		AObstacleTile* Tile = World->SpawnActor<AObstacleTile>(FloorTileClass, NextSpawnPoint);
		// Tile->SetLifeSpan(TileLifeSpan);
		
		if (Tile)
		{
			FloorTileArray.Add(Tile);
			
			if(SpawnItems)
			{
				Tile->SpawnItems();
			}
			
			NextSpawnPoint = Tile->GetAttachmentTransform();
			const FVector NextSpawnLoc = NextSpawnPoint.GetLocation();
			NextSpawnPoint.SetLocation({NextSpawnLoc.X + Tile->GetFloorBounds().X, NextSpawnLoc.Y, NextSpawnLoc.Z});
		}

		return Tile;
	}

	return nullptr;
}

/*
 *	Add one on the coin counter
 */
void AEndlessRunnerGameMode::AddCoin()
{
	TotalCoins++;
	OnCoinCountChanged.Broadcast(TotalCoins);
}

/*
 *	Shows game over GUI
 */
void AEndlessRunnerGameMode::GameOver()
{
	if(IsValid(GameOverClass))
	{
		if(UUserWidget* const GameOverWidget = CreateWidget(GetWorld(), GameOverClass))
		{
			GameOverWidget->AddToViewport();
		}
	}
}

/*
 *	Prepare world for the next player live
 */
void AEndlessRunnerGameMode::PlayerDied()
{
	CurrentLives--;
	OnLivesCountChanged.Broadcast(CurrentLives);

	if(CurrentLives > 0)
	{
		for(auto Tile : FloorTileArray)
		{
			Tile->DestroyFloorTile();
		}

		FloorTileArray.Empty();
		NextSpawnPoint = FTransform{};

		CreateInitialFloorTiles(NumInitialFloorTiles);
		// NextSpawnPoint = FTransform();
		//
		// for(int i = 0; i < TilesPool->GetPoolSize(); i++)
		// {
		// 	if(APooledObject* PooledObject = Cast<AObstacleTile>(TilesPool->SpawnPooledObject(NextSpawnPoint)); IsValid(PooledObject))
		// 	{
		// 		AObstacleTile* const FloorTile = Cast<AObstacleTile>(PooledObject);
		// 		FloorTile->PrepareNextTile(); 
		// 		// AddFloorTile(true);
		// 	}
		// }
		//
		// // FloorTiles.Empty();
		// NextSpawnPoint = FTransform();
		// CreateInitialFloorTiles(NumInitialFloorTiles);
		OnLevelReset.Broadcast();
	}
	else
	{
		GameOver();
	}
}
