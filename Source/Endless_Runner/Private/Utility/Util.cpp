#include "Utility/Util.h"
#include "Engine/StaticMesh.h"

UStaticMesh* Util::GetRandomStaticMesh(const TArray<UStaticMesh*>& Array)
{
	if (Array.Num() >= 0) 
	{
		const float RandValue = FMath::RandRange(0, Array.Num() - 1);
		return Array[RandValue];
	}
	
	return nullptr;
}
