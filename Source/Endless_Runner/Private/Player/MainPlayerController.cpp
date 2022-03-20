// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayerController.h"
#include "Player/PlayerBase.h"

AMainPlayerController::AMainPlayerController()
{
}

void AMainPlayerController::BeginPlay()
{
	CurrentPawn = Cast<APlayerBase>(GetPawn());
}

void AMainPlayerController::Start()
{
	CurrentPawn->ActiveRun() = true;
}

auto AMainPlayerController::MoveRight() -> void
{
	CurrentPawn->MoveRight();
}

void AMainPlayerController::MoveLeft()
{
	CurrentPawn->MoveLeft();
}

void AMainPlayerController::Jump()
{
	CurrentPawn->Jump();
}

auto AMainPlayerController::MoveDown() -> void
{
	CurrentPawn->MoveDown();
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Start", IE_Pressed, this, &AMainPlayerController::Start);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &AMainPlayerController::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &AMainPlayerController::MoveLeft);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &AMainPlayerController::MoveDown);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayerController::Jump);
	// InputComponent->BindAction("Jump", IE_Released, this, &AMainPlayerController::MoveDown);
}
