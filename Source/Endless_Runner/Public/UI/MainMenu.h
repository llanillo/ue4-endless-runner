// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

UCLASS()
class ENDLESS_RUNNER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StartBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitBtn;

	UFUNCTION()
	void OnStartClick();

	UFUNCTION()
	void OnQuitClick();

protected:

	virtual void NativeConstruct() override;
};
