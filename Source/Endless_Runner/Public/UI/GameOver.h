// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

class UButton;

UCLASS()
class ENDLESS_RUNNER_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MainMenuBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartBtn;

	UFUNCTION()
	void OnMainMenuClick();

	UFUNCTION()
	void OnRestartClick();

protected:

	virtual void NativeConstruct() override;
	
};
