#pragma once

#include "EquipmentComponentUIState.h"
#include "EquipmentComponentUIStateHolder.generated.h"

UINTERFACE(Blueprintable)
class UEquipmentComponentUIStateHolder : public UInterface
{
	GENERATED_BODY()
};

class IEquipmentComponentUIStateHolder
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FEquipmentComponentUIState GetUIState();
};
