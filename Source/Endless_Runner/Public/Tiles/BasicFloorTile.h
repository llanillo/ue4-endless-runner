// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "BasicFloorTile.generated.h"

class USceneComponent;
class UBoxComponent;
class AWallObstacle;
class AEndlessRunnerGameMode;

UCLASS()
class ENDLESS_RUNNER_API ABasicFloorTile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleInstanceOnly)
	AEndlessRunnerGameMode* MainGameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWallObstacle> SmallObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWallObstacle> BigObstacleClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FloorMesh;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	FTimerHandle DestroyHandle;

	UFUNCTION(BlueprintCallable)
	void SpawnLaneItem(const UArrowComponent* Lane) const;

	UFUNCTION(BlueprintCallable)
	void DestroyFloorTile();
	
	UFUNCTION(BlueprintInternalUseOnly)
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	
	// Sets default values for this actor's properties
	ABasicFloorTile();

	UFUNCTION(BlueprintCallable)
	void SpawnItems();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	FORCEINLINE const FTransform& GetAttachmentTransform() const { return AttachPoint->GetComponentTransform(); }

	FORCEINLINE const UArrowComponent* GetCenterLane() const { return CenterLane; }

	FORCEINLINE const UArrowComponent* GetRightLane() const {return RightLane;}

	FORCEINLINE const UArrowComponent* GetLeftLane() const {return LeftLane;}
	
};
