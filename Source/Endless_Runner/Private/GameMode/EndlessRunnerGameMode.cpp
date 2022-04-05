// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/EndlessRunnerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/ArrowComponent.h"
#include "Tiles/FloorTile.h"
#include "Tiles/ObstacleTile.h"
#include "UI/GameHud.h"

void AEndlessRunnerGameMode::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud);

	GameHud->InitializeHud(this);
	GameHud->AddToViewport();

	CreateInitialFloorTiles();

	CurrentLives = MaxLives;
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
	AddFloorTile(false);
	
	for (int i = 0; i < NumInitialFloorTiles; i++) 
	{
		AddFloorTile(true); 
	}
}

void AEndlessRunnerGameMode::RemoveTile(AFloorTile* Tile)
{
	FloorTiles.Remove(Tile);
}

AObstacleTile* AEndlessRunnerGameMode::AddFloorTile(const bool SpawnItems)
{
	UWorld* World = GetWorld();
	
	if (World)
	{
		AObstacleTile* Tile = World->SpawnActor<AObstacleTile>(FloorTileClass, NextSpawnPoint);

		if (Tile)
		{
			FloorTiles.Add(Tile);
			
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
		for(AFloorTile* FloorTile : FloorTiles)
		{
			FloorTile->DestroyFloorTile();
		}

		FloorTiles.Empty();
		NextSpawnPoint = FTransform();
		CreateInitialFloorTiles();
		OnLevelReset.Broadcast();
	}
	else
	{
		GameOver();
	}
}
