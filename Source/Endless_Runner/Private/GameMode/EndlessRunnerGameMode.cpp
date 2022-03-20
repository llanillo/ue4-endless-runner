// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/EndlessRunnerGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "Tiles/BasicFloorTile.h"
#include "UI/GameHud.h"

void AEndlessRunnerGameMode::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud);

	GameHud->InitializeHud(this);
	GameHud->AddToViewport();
	CreateInitialFloorTiles();
}

void AEndlessRunnerGameMode::CreateInitialFloorTiles()
{
	ABasicFloorTile* Tile = AddFloorTile(false);

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

ABasicFloorTile* AEndlessRunnerGameMode::AddFloorTile(const bool SpawnItems)
{
	UWorld* World = GetWorld();
	
	if (World)
	{
		ABasicFloorTile* Tile = World->SpawnActor<ABasicFloorTile>(FloorTileClass, NextSpawnPoint);

		if (Tile)
		{
			if(SpawnItems)
			{
				Tile->SpawnItems();
			}
			
			NextSpawnPoint = Tile->GetAttachmentTransform();
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
