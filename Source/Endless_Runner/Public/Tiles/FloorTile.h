// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment/Pool/ObjectPool.h"
#include "Environment/Pool/PooledObject.h"
#include "FloorTile.generated.h"

class ACoinItem;
class USceneComponent;
class UBoxComponent;
class AObstacle;
class AEndlessRunnerGameMode;
class UArrowComponent;

UCLASS()
class ENDLESS_RUNNER_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode")
	AEndlessRunnerGameMode* MainGameMode;
	
	UPROPERTY(VisibleAnywhere, Category = "Child Actors")
	TArray<AActor*> ChildActors;
	
	UPROPERTY(BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	FTimerHandle DestroyTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> SideTileMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> FloorMeshes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACoinItem> CoinItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UObjectPool* FloorTilePool;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FloorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftSideMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightSideMesh;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* FloorRoadMesh;
    	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* AttachPoint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* FloorTriggerBox;

	UFUNCTION(BlueprintInternalUseOnly)
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	UStaticMesh* GetRandomSideMesh() const;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

	UPROPERTY()
	float LifeSpan = 2.0f;
	
	UFUNCTION()
	void DestroyChildActors();

public:
	// virtual void SetLifeSpan(float InLifespan) override;


	// UFUNCTION(BlueprintCallable)
	// void PrepareNextTile();

	UFUNCTION(BlueprintCallable)
	void DestroyFloorTile();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AddChildActor(AActor* ChildActor)  { ChildActors.Add(ChildActor); }
	
	FORCEINLINE USceneComponent* GetSceneComponent() const;
	FORCEINLINE const TSubclassOf<ACoinItem>& GetCoinItemClass() const;
	FORCEINLINE const TArray<UStaticMesh*>& GetFloorMeshes() const;
	
public:

	AFloorTile();
	
	UStaticMeshComponent* GetFloorRoadMesh() const { return FloorRoadMesh; };
	FORCEINLINE const FTransform& GetAttachmentTransform() const;
	FORCEINLINE FVector GetFloorBounds() const;
};
