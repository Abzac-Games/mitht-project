#pragma once

#include "CoreMinimal.h"
#include "EquipmentComponentUIState.h"
#include "GameFramework/HUD.h"
#include "ProjectHUD.generated.h"

/**
 * HUD of the project.
 */
UCLASS(Abstract)
class MITHT_PROJECT_API AProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetEquipmentComponentUIState(const FEquipmentComponentUIState& State);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveEquipmentComponentUIState();
};
