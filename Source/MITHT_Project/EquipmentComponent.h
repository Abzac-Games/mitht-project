#pragma once

#include "CoreMinimal.h"
#include "EquipmentComponentUIStateHolder.h"
#include "SMStateMachineComponent.h"
#include "Components/ActorInteractableComponent.h"
#include "GameFramework/Actor.h"
#include "EquipmentComponent.generated.h"

UCLASS(Abstract)
class MITHT_PROJECT_API AEquipmentComponent : public AActor, public IEquipmentComponentUIStateHolder
{
	GENERATED_BODY()

public:
	AEquipmentComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UActorInteractableComponent> Interactable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USMStateMachineComponent> StateMachine;
};
