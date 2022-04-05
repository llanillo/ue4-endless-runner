#include "Obstacles/Obstacle.h"
#include "Utility/Util.h"
#include "Player/PlayerBase.h"

// Sets default values
AObstacle::AObstacle()
{
 	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(SceneComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentHit.AddDynamic(this, &AObstacle::OnObstacleHit);
	MeshComponent->SetStaticMesh(Util::GetRandomStaticMesh(ObstacleMeshes));
}

void AObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APlayerBase* Player = Cast<APlayerBase>(OtherActor);
	
	if(Player)
	{
		Player->Death();
	}
}
