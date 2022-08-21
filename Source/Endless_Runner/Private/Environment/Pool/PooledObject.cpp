// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Environment/Pool/PooledObject.h"
#include "Environment/Pool/PooledObject.h"

void APooledObject::OnSpawn()
{
}

// Sets default values
APooledObject::APooledObject()
{
	
}

void APooledObject::SetLifeSpan(const float InLifespan)
{
	LifeSpan = InLifespan;
}

float APooledObject::GetLifeSpan() const
{
	return LifeSpan;
}
