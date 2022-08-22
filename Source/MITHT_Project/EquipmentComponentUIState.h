#pragma once

#include "CoreMinimal.h"
#include "EquipmentComponentUIState.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentComponentUIState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText State;
};
