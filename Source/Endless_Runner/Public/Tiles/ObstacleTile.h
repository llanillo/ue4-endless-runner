#pragma once

#include "CoreMinimal.h"
#include "Tiles/FloorTile.h"
#include "ObstacleTile.generated.h"

UCLASS()
class ENDLESS_RUNNER_API AObstacleTile : public AFloorTile
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* RightLane;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RoadMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AObstacle> SmallObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AObstacle> BigObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpawnPercent1 = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpawnPercent2 = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpawnPercent3 = 1.0f;

public:

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnItems();
	
private:

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnLaneItem(const UArrowComponent* Lane, int32& NumBigWalls);
	
protected:
	
	virtual void BeginPlay() override;
	
public:

	AObstacleTile();

	FORCEINLINE const UArrowComponent* GetCenterLane() const { return CenterLane; }
	FORCEINLINE const UArrowComponent* GetRightLane() const { return RightLane; }
	FORCEINLINE const UArrowComponent* GetLeftLane() const { return LeftLane; }
	
};
