// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallObstacle.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ENDLESS_RUNNER_API AWallObstacle : public AActor
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	AWallObstacle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

protected:
	virtual void BeginPlay() override;
};
