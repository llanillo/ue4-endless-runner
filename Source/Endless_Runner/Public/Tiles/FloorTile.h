// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

class ACoinItem;
class USceneComponent;
class UBoxComponent;
class AWallObstacle;
class AEndlessRunnerGameMode;
class UArrowComponent;

UCLASS()
class ENDLESS_RUNNER_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleInstanceOnly)
	AEndlessRunnerGameMode* MainGameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWallObstacle> SmallObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWallObstacle> BigObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<ACoinItem> CoinItemClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* RightLane;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* LeftLane;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* FloorTriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> ChildActors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	FTimerHandle DestroyHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpawnPercent1 = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpawnPercent2 = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpawnPercent3 = 0.5f;
	
	UFUNCTION(BlueprintCallable)
	void SpawnLaneItem(const UArrowComponent* Lane, int32& NumBigWalls);
	
	UFUNCTION(BlueprintInternalUseOnly)
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FloorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LeftBlockMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UStaticMeshComponent* RightBlockMesh;
	
public:
	
	// Sets default values for this actor's properties
	AFloorTile();

	UFUNCTION(BlueprintCallable)
	void SpawnItems();

	UFUNCTION(BlueprintCallable)
	void DestroyFloorTile();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	FORCEINLINE const FTransform& GetAttachmentTransform() const;

	FORCEINLINE const UArrowComponent* GetCenterLane() const { return CenterLane; }

	FORCEINLINE const UArrowComponent* GetRightLane() const { return RightLane; }

	FORCEINLINE const UArrowComponent* GetLeftLane() const { return LeftLane; }

	FORCEINLINE FVector GetFloorBounds() const;
};
