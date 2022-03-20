// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"
#include "Components/Button.h"

void UPauseMenu::OnContinueClick()
{
}

void UPauseMenu::OnRestartClick()
{
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
