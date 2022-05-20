// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment/Pool/ObjectPool.h"
#include "Environment/Pool/PooledObject.h"

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
		PooledObject->SetActorHiddenInGame(false);
		PooledObject->OnSpawn();
		PooledObject->TeleportTo(Transform.GetLocation(), Transform.GetRotation().Rotator());
		ObjectPoolQueue.Enqueue(PooledObject);
		return PooledObject;
	}

	return nullptr;
}

void UObjectPool::InitializePool(const FTransform& InitialTransform)
{
	if(IsValid(PooledObjectClass))
	{
		if(UWorld* const World = GetWorld())
		{
			for(int i = 0; i < PoolSize; i++)
			{
				if(APooledObject* const PooledActor = World->SpawnActor<APooledObject>(PooledObjectClass, InitialTransform))
				{
					PooledActor->SetLifeSpan(ObjectLifeSpan);
					PooledActor->SetActorHiddenInGame(true);
					ObjectPoolQueue.Enqueue(PooledActor);
				}
			}
		}
	}
}

void UObjectPool::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	PoolActor->SetActorHiddenInGame(true);
}

int32 UObjectPool::GetPoolSize() const
{
	return PoolSize;
}

TQueue<APooledObject*>& UObjectPool::GetPoolQueue()
{
	return ObjectPoolQueue;
}
