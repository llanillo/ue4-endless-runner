// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/CoinItem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Player/PlayerBase.h"

void ACoinItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APlayerBase* MainCharacter = Cast<APlayerBase>(OtherActor);

	if(MainCharacter && OverlapSound)
	{
		MainGameMode->AddCoin();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
		Destroy();
	}
	
}

// Sets default values
ACoinItem::ACoinItem()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereComponent->SetupAttachment(SceneComponent);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapPawnOnly"));
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(SphereComponent);
	MeshComponent->SetCollisionProfileName(TEXT("OverlapPawnOnly"));

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovementComponent->RotationRate = FRotator(0, 180, 0);	
}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();

	MainGameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(MainGameMode);
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoinItem::OnSphereOverlap);
}