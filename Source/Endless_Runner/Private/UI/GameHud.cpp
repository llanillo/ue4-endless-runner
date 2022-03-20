// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHud.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGameHud::OnPauseClick()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UUserWidget* UserWidget = CreateWidget(GetWorld(), PauseMenuWidgetClass);
	
	if(UserWidget)
	{
		UserWidget->AddToViewport();
		UserWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UGameHud::InitializeHud(AEndlessRunnerGameMode* MainGameMode)
{
	if(MainGameMode)
	{
		CoinCount->SetText(FText::AsNumber(0));
		MainGameMode->OnCoinCountChanged.AddDynamic(this, &UGameHud::SetCoinCount);
	}	
}

void UGameHud::SetCoinCount(int32 CoinsCount)
{
	CoinCount->SetText(FText::AsNumber(CoinsCount));
}

void UGameHud::NativeConstruct()
{
	Super::NativeConstruct();

	if(PauseBtn)
	{
		PauseBtn->OnClicked.AddDynamic(this, &UGameHud::OnPauseClick);
	}
	
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}
