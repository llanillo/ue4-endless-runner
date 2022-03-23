// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainMenuGameMode.h"
#include "blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(MainMenuClass))
	{
		UUserWidget* MainMenuWidget = CreateWidget(GetWorld(), MainMenuClass);

		if(MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
