// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UButton;

UCLASS()
class ENDLESS_RUNNER_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ContinueBtn;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartBtn;

	UFUNCTION()
	void OnContinueClick();

	UFUNCTION()
	void OnRestartClick();
	
protected:

	virtual void NativeConstruct() override;
};
