// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

UCLASS()
class ENDLESS_RUNNER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	class APlayerBase* CurrentPawn;
	
public:
	AMainPlayerController();

protected:
	
	virtual void BeginPlay() override;
	
	void Start();
	void MoveRight();
	void MoveLeft();
	void Jump();
	void MoveDown();

public:
	virtual void SetupInputComponent() override;

};