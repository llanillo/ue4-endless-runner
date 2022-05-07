// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/Pool/PooledObject.h"
#include "Environment/Pool/ObjectPool.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
}

APooledObject* UObjectPool::SpawnPooledObject(const FTransform& Transform)
{
	if(!ObjectPoolQueue.IsEmpty())
	{
		APooledObject* PooledObject;
		ObjectPoolQueue.Dequeue(PooledObject);
		PooledObject->SetActive(true);
		PooledObject->TeleportTo(Transform.GetLocation(), Transform.GetRotation().Rotator());
		ObjectPoolQueue.Enqueue(PooledObject);
		return PooledObject;
	}

	return nullptr;
}

void UObjectPool::InitializePool()
{
	if(IsValid(PooledObjectClass))
	{
		UWorld* const World = GetWorld();
		
		if(World)
		{
			for(int i = 0; i < PoolSize; i++)
			{
				APooledObject* const PooledActor = World->SpawnActor<APooledObject>(PooledObjectClass, FVector().ZeroVector, FRotator().ZeroRotator);
				
				if(PooledActor)
				{
					PooledActor->OnPooledObjectDespawn.AddDynamic(this, &UObjectPool::OnPooledObjectDespawn);
					PooledActor->SetLifeSpan(ObjectLifeSpan);
					PooledActor->SetActive(false);
					ObjectPoolQueue.Enqueue(PooledActor);
				}
			}
		}
	}
}

void UObjectPool::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	ObjectPoolQueue.Enqueue(PoolActor);
}

int32 UObjectPool::GetPoolSize()
{
	return PoolSize;
}

TQueue<APooledObject*>& UObjectPool::GetPoolQueue()
{
	return ObjectPoolQueue;
}
