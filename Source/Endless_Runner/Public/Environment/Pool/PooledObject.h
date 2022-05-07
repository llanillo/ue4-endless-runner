// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

// class APooledObject;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);

UCLASS()
class ENDLESS_RUNNER_API APooledObject : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateACcess = "true"))
	FTimerHandle LifeSpanTimer;
	
	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
	void Desactivate();
public:	

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnPooledObjectDespawn OnPooledObjectDespawn;

private:

	float LifeSpan;

public:
	
	// Sets default values for this actor's properties
	APooledObject();
	
	virtual void SetLifeSpan(float InLifespan) override;
	void SetActive(bool IsActive);
};
