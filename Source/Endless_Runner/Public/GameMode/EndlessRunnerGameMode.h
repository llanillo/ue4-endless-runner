// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

class UUserWidget;
class AFloorTile;
class AObstacleTile;
class UObjectPool;
class APooledObject;
class UGameHud;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinCountChanged, int32, CoinCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChanged, int32, LivesCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReset);

UCLASS()
class ENDLESS_RUNNER_API AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	// UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// UObjectPool* TilesPool;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, NoClear, Category = "Config", meta = (AllowPrivateAccess = "true"))
	int32 NumInitialFloorTiles = 10;
	
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> GameHudClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> GameOverClass;

	UPROPERTY(EditAnywhere, Category = "Runtime")
	TSubclassOf<AObstacleTile> FloorTileClass;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Widget")
	UGameHud* GameHud;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<AFloorTile*> FloorTileArray;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint {};

	UPROPERTY(BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	int32 TotalCoins = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLives = 0;

	UPROPERTY(EditAnywhere, Category = "Player")
	int32 MaxLives = 3;

	UPROPERTY(EditAnywhere, Category = "RunTime")
	float TileLifeSpan = 2.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Runtime")
	void CreateInitialFloorTiles(int InitialFloorTiles);


public:

	UFUNCTION(BlueprintCallable, Category = "Runtime")
	AObstacleTile* AddFloorTile(bool SpawnItems);
	
	UFUNCTION(BlueprintCallable)
	void RemoveTile(AFloorTile* Tile);
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void AddCoin();

	UFUNCTION(BlueprintCallable, Category = "Runtime")
	void GameOver();
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void PlayerDied();
	
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

	AEndlessRunnerGameMode();
	
	FORCEINLINE const TArray<float>& GetLaneValues() const { return LaneSwitchValues; }
	FORCEINLINE const int32& GetMaxLives() const { return MaxLives; }

};
