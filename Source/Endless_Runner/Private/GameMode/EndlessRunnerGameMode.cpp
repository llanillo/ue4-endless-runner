// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/EndlessRunnerGameMode.h"
#include "Tiles/BasicFloorTile.h"

void AEndlessRunnerGameMode::BeginPlay()
{
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
