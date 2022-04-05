// Fill out your copyright notice in the Description page of Project Settings.

#include "Tiles/FloorTile.h"
#include "Collectables/CoinItem.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Player/PlayerBase.h"
#include "GameMode/EndlessRunnerGameMode.h"
#include "Kismet/KismetMathLibrary.h"

AFloorTile::AFloorTile()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;
	
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);

	LeftSideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBlockMesh"));
	LeftSideMesh->SetupAttachment(SceneComponent);
	
	RightSideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBlockMesh"));
	RightSideMesh->SetupAttachment(SceneComponent);

	FloorRoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Road Mesh"));
	FloorRoadMesh->SetupAttachment(SceneComponent);
	
	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Point"));
	AttachPoint->SetupAttachment(SceneComponent);
	
	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Floor Trigger Box"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.0f, 500.0f, 200.0f));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	// Get the main mode reference
	MainGameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(MainGameMode);

	// Add Overlap event to floor component
	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnTriggerBoxOverlap);

	// Assign random mesh to sides
	LeftSideMesh->SetStaticMesh(GetRandomSideMesh());
	RightSideMesh->SetStaticMesh(GetRandomSideMesh());
}

const FTransform& AFloorTile::GetAttachmentTransform() const
{
	return AttachPoint->GetComponentTransform();
}

FVector AFloorTile::GetFloorBounds() const
{
	return FloorMesh->CalcBounds(FloorMesh->GetComponentTransform()).BoxExtent;
}

USceneComponent* AFloorTile::GetSceneComponent() const
{
	return SceneComponent;
}

const TSubclassOf<ACoinItem>& AFloorTile::GetCoinItemClass() const
{
	return CoinItemClass; 
}

void AFloorTile::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APlayerBase* MainCharacter = Cast<APlayerBase>(OtherActor);

	if (MainCharacter)
	{
		MainGameMode->AddFloorTile(true);
		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFloorTile::DestroyFloorTile, 2.0f, false);
	}
}

UStaticMesh* AFloorTile::GetRandomSideMesh() const
{
	const int32 ArraySize = SideTileMeshes.Num();
	if(ArraySize > 0)
	{
		const int32 RandValue = FMath::RandRange(0, ArraySize - 1);
		return SideTileMeshes[RandValue];
	}
	return nullptr;
}

void AFloorTile::DestroyFloorTile()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	for(AActor* Actor : ChildActors)
	{
		if(IsValid(Actor))
		{
			Actor->Destroy();
		}
	}

	ChildActors.Empty();
	MainGameMode->RemoveTile(this);
	Destroy();
}
