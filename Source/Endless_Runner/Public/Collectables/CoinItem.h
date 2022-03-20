// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameMode/EndlessRunnerGameMode.h"
#include "CoinItem.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
class URotatingMovementComponent;
class USoundBase; 

UCLASS()
class ENDLESS_RUNNER_API ACoinItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly)
	AEndlessRunnerGameMode* MainGameMode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	URotatingMovementComponent* RotatingMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USoundBase* OverlapSound;
	
	UFUNCTION(BlueprintInternalUseOnly)
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool  bFromSweep, const FHitResult &SweepResult);
	
public:	
	// Sets default values for this actor's properties
	ACoinItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
