// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/EndlessRunnerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/ArrowComponent.h"
#include "Tiles/FloorTile.h"
#include "Tiles/ObstacleTile.h"
#include "Environment/Pool/ObjectPool.h"
#include "Environment/Pool/PooledObject.h"
#include "UI/GameHud.h"

void AEndlessRunnerGameMode::BeginPlay()
{
	// SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	// RootComponent = SceneComponent;
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud);
	
	GameHud->InitializeHud(this);
	GameHud->AddToViewport();

	CurrentLives = MaxLives;
	
	TilesPool->InitializePool();
	CreateInitialFloorTiles();
}

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	TilesPool = CreateDefaultSubobject<UObjectPool>(TEXT("Floor Tiles Pool"));
	AddOwnedComponent(TilesPool);
}

void AEndlessRunnerGameMode::CreateInitialFloorTiles()
{
	const AObstacleTile* Tile = AddFloorTile(false);
	
	if (Tile)
	{
		LaneSwitchValues.Add(Tile->GetLeftLane()->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->GetCenterLane()->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->GetRightLane()->GetComponentLocation().Y);
	}
	
	AddFloorTile(false);
	
	for (int i = 0; i < NumInitialFloorTiles; i++) 
	{
		AddFloorTile(true); 
	}
}

AObstacleTile* AEndlessRunnerGameMode::AddFloorTile(const bool SpawnItems)
{
	if (GetWorld())
	{
		// AObstacleTile* Tile = World->SpawnActor<AObstacleTile>(FloorTileClass, NextSpawnPoint);
		AObstacleTile* Tile = Cast<AObstacleTile>(TilesPool->SpawnPooledObject(NextSpawnPoint));
		
		if (Tile)
		{
			// FloorTiles.Add(Tile);
			Tile->SetActive(true);
			
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

void AEndlessRunnerGameMode::AddCoin()
{
	TotalCoins++;
	OnCoinCountChanged.Broadcast(TotalCoins);
}

void AEndlessRunnerGameMode::GameOver()
{
	if(IsValid(GameOverClass))
	{
		UUserWidget* GameOverWidget = CreateWidget(GetWorld(), GameOverClass);

		if(GameOverWidget)
		{
			GameOverWidget->AddToViewport();
		}
	}
}

void AEndlessRunnerGameMode::PlayerDied()
{
	CurrentLives--;
	OnLivesCountChanged.Broadcast(CurrentLives);

	if(CurrentLives > 0)
	{
		for(int i = 0; i < TilesPool->GetPoolSize(); i++)
		{
			APooledObject* PooledObject;
			TilesPool->GetPoolQueue().Dequeue(PooledObject);

			if(IsValid(PooledObject))
			{
				AObstacleTile* const FloorTile = Cast<AObstacleTile>(PooledObject);
				FloorTile->DestroyFloorTile();
				TilesPool->GetPoolQueue().Enqueue(FloorTile);
			}
		}
		
		// FloorTiles.Empty();
		NextSpawnPoint = FTransform();
		CreateInitialFloorTiles();
		OnLevelReset.Broadcast();
	}
	else
	{
		GameOver();
	}
}
