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
class ENDLESS_RUNNER_API AFloorTile : public APooledObject
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "Game Mode", meta = (AllowPrivateAccess))
	AEndlessRunnerGameMode* MainGameMode;
	
	UPROPERTY(BlueprintReadOnly, Category = "Child Actors", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> ChildActors;
	
	UPROPERTY(BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	FTimerHandle DestroyTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> SideTileMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACoinItem> CoinItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UObjectPool* FloorTilePool;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FloorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftSideMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes", meta = (AllowPrivateAccess = "true"))
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

public:
	
	UFUNCTION(BlueprintCallable)
	void DestroyFloorTile();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AddChildActor(AActor* ChildActor)  { ChildActors.Add(ChildActor); }

	FORCEINLINE USceneComponent* GetSceneComponent() const;
	FORCEINLINE const TSubclassOf<ACoinItem>& GetCoinItemClass() const;
	
public:

	AFloorTile();
	
	UStaticMeshComponent* GetFloorRoadMesh() const { return FloorRoadMesh; };
	FORCEINLINE const FTransform& GetAttachmentTransform() const;
	FORCEINLINE FVector GetFloorBounds() const;
};
