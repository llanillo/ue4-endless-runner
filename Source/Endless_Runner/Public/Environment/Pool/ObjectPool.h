// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"

class APooledObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESS_RUNNER_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Pool", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APooledObject> PooledObjectClass;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool", meta = (AllowPrivateAccess = "true"))
	int32 PoolSize = 20;

	UPROPERTY(EditAnywhere, NoClear, Category = "Object Pool", meta = (AllowPrivateAccess = "true"))
	float ObjectLifeSpan;
	
	TQueue<APooledObject*> ObjectPoolQueue;
	
public:	
	// Sets default values for this component's properties
	UObjectPool();

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	APooledObject* SpawnPooledObject(const FTransform& Transform);

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void InitializePool();
	
	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);

	TQueue<APooledObject*>& GetPoolQueue(); 
	int32 GetPoolSize();
};
