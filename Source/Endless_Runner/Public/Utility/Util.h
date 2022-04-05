#pragma once

#include "CoreMinimal.h"

class UStaticMesh;

namespace Util
{
	UStaticMesh* GetRandomStaticMesh(const TArray<UStaticMesh*>& Array); 
}