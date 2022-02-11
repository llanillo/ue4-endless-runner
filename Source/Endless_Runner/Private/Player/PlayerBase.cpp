// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameMode/EndlessRunnerGameMode.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerBase::APlayerBase()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a camera arm (moves the camera if there is a collision blocking its vision)
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	// Create the camera that will follow the player
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArmComp);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerBase::ChangeLaneUpdate(const float Value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(MainGameMode->GetLaneValues()[CurrentLane], MainGameMode->GetLaneValues()[NextLane], Value);
	SetActorLocation(Location);
}

void APlayerBase::ChangeLaneFinished()
{
	CurrentLane = NextLane;
}

void APlayerBase::Death()
{
	if(!IsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Muerto"));
		const UWorld* World = GetWorld();
		IsDead = true;
		DisableInput(nullptr);
		if(World && DeathParticleSystem && DeathSound)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, DeathParticleSystem, GetActorLocation());
			GetMesh()->SetVisibility(false);
			World->GetTimerManager().SetTimer(RestartTimeHandle, this, &APlayerBase::OnDeath, 1.0f);
		}
	}
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
	MainGameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    OnActorHit.AddDynamic(this, &APlayerBase::Test);
}

void APlayerBase::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	ChangeLane();
}

void APlayerBase::MoveLeft()
{
	NextLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();
}

void APlayerBase::MoveForward()
{
	if (IsRunning)
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Roll = 0.0f;
		Rotation.Pitch = 0.0f;
		AddMovementInput(Rotation.Vector());
	}
}

void APlayerBase::Test(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Choco"));
}

void APlayerBase::Tick(float DeltaTime)
{
	MoveForward();
}

void APlayerBase::OnDeath()
{
	if(RestartTimeHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RestartTimeHandle);
	}

	IsDead = false;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}
