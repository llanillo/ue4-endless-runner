// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "UI/GameHud.h"
#include "Components/Button.h"

void UPauseMenu::OnContinueClick()
{
	UWorld* World = GetWorld();

	if(World)
	{
	    UGameplayStatics::SetGamePaused(World, false);
		// RemoveFromParent();
	}
}

void UPauseMenu::OnRestartClick()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));	
	}
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if(RestartBtn && ContinueBtn)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnRestartClick);
		ContinueBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnContinueClick);
	}
}
