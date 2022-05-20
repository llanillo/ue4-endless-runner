// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

UCLASS()
class ENDLESS_RUNNER_API APooledObject : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Object Pool", meta = (AllowPrivateACcess = "true"))
	FTimerHandle LifeSpanTimer;

public:

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	virtual void OnSpawn();
	
private:
	float LifeSpan;


public:
	// Sets default values for this actor's properties
	APooledObject();
	
	virtual void SetLifeSpan(float InLifespan) override;

protected:

	FORCEINLINE virtual float GetLifeSpan() const override;
	FORCEINLINE FTimerHandle& GetLifeSpanTimer() { return LifeSpanTimer; }
};
