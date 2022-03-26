// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

class UUserWidget;
class AFloorTile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinCountChanged, int32, CoinCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChanged, int32, LivesCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReset);

UCLASS()
class ENDLESS_RUNNER_API AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameHud* GameHud;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> GameHudClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> GameOverClass;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AFloorTile> FloorTileClass;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<AFloorTile*> FloorTiles;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialFloorTiles = 10;

	UPROPERTY(VisibleAnywhere, Category = "Collectables")
	int32 TotalCoins = 0;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	int32 CurrentLives = 0;

	UPROPERTY(EditAnywhere, Category = "Player")
	int32 MaxLives = 3;
	
	UFUNCTION(BlueprintCallable, Category = "Tiles")
	void CreateInitialFloorTiles();

public:
	
	UFUNCTION(BlueprintCallable)
	AFloorTile* AddFloorTile(const bool SpawnItems);

	UFUNCTION(BlueprintCallable, Category = "Collectables")
	void AddCoin();

	UFUNCTION(BlueprintCallable, Category = "Config")
	void GameOver();
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void PlayerDied();

	UFUNCTION(BlueprintCallable, Category = "Tiles")
	void RemoveTile(AFloorTile* Tile);
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnCoinCountChanged OnCoinCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnLivesCountChanged OnLivesCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnLevelReset OnLevelReset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	FORCEINLINE const TArray<float>& GetLaneValues() const { return LaneSwitchValues; }
	
	FORCEINLINE int32 GetMaxLives() const { return MaxLives; }

};
