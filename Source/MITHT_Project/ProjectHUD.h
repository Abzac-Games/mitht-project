#pragma once

#include "CoreMinimal.h"
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
	void SetComponentName(const FText& ComponentName);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveComponentName();
};
