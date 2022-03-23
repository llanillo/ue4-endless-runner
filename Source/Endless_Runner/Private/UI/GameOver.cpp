// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOver.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::OnMainMenuClick()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenuLevel"));
	}
}

void UGameOver::OnRestartClick()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	if(RestartBtn)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UGameOver::OnRestartClick);
	}

	if(MainMenuBtn)
	{
		MainMenuBtn->OnClicked.AddDynamic(this, &UGameOver::OnMainMenuClick);
	}
}
