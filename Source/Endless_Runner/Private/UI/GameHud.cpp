// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHud.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGameHud::OnPauseClick()
{
	if(IsValid(PauseMenuWidgetClass))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		UUserWidget* UserWidget = CreateWidget(GetWorld(), PauseMenuWidgetClass);

		if(UserWidget)
		{
			UserWidget->AddToViewport();
			UserWidget->SetVisibility(ESlateVisibility::Visible);
			RemoveFromParent();
		}	
	}
}

void UGameHud::InitializeHud(AEndlessRunnerGameMode* MainGameMode)
{
	if(MainGameMode)
	{
		CoinCount->SetText(FText::AsNumber(0));
		LivesCount->SetText(FText::AsNumber(MainGameMode->GetMaxLives()));
		
		MainGameMode->OnCoinCountChanged.AddDynamic(this, &UGameHud::SetCoinCount);
		MainGameMode->OnLivesCountChanged.AddDynamic(this, &UGameHud::SetLivesCount);
	}	
}

void UGameHud::SetCoinCount(int32 Count)
{
	CoinCount->SetText(FText::AsNumber(Count));
}

void UGameHud::SetLivesCount(int32 Count)
{
	LivesCount->SetText(FText::AsNumber(Count));
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