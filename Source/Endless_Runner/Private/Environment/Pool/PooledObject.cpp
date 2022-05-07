// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Pool/PooledObject.h"

void APooledObject::Desactivate()
{
	if(LifeSpanTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(LifeSpanTimer);
	}
	
	OnPooledObjectDespawn.Broadcast(this);
}

// Sets default values
APooledObject::APooledObject()
{
		
}

void APooledObject::SetActive(bool IsActive)
{
	if(!IsActive)
	{
		GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APooledObject::Desactivate, LifeSpan, false);
	}

	SetActorHiddenInGame(!IsActive);
}

void APooledObject::SetLifeSpan(float InLifespan)
{
	LifeSpan = InLifespan;
}
