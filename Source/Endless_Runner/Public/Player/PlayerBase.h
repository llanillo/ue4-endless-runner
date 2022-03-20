// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AEndlessRunnerGameMode;
class UParticleSystem;
class USoundBase;

UCLASS()
class ENDLESS_RUNNER_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DeathParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets", meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float MoveDownImpulse = -500.0f;
	
	UPROPERTY(VisibleInstanceOnly)
	AEndlessRunnerGameMode* MainGameMode;

	UPROPERTY(VisibleInstanceOnly)
	FTimerHandle RestartTimeHandle;
	
	UPROPERTY(VisibleInstanceOnly)
	int32 CurrentLane = 1;

	UPROPERTY(VisibleInstanceOnly)
	int32 NextLane = 0;
	
	UPROPERTY(VisibleInstanceOnly)
	bool IsDead = false;

	UPROPERTY(VisibleInstanceOnly)
	bool IsRunning = false;

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneUpdate(const float Value);

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneFinished();
	
	void MoveForward();
	void OnDeath();

public:
	// Sets default values for this character's properties
	APlayerBase();

	UFUNCTION(BlueprintCallable)
	void Death();
	
	UFUNCTION(BlueprintCallable)
	void MoveRight();

	UFUNCTION(BlueprintCallable)
	void MoveLeft();

	UFUNCTION(BlueprintCallable)
	void MoveDown();
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
	void ChangeLane();
	
public:		
	
	FORCEINLINE USpringArmComponent* GetSpringArmCamera() const { return SpringArmComp; }

	FORCEINLINE UCameraComponent* GetCamera() const { return FollowCamera; }

	FORCEINLINE bool& ActiveRun() { return IsRunning; }
};
