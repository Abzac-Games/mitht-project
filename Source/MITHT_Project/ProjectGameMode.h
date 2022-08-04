#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/ActorInteractableComponent.h"
#include "Components/ActorInteractorComponent.h"
#include "ProjectGameMode.generated.h"

/**
 * Game mode of the project.
 */
UCLASS()
class MITHT_PROJECT_API AProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UActorInteractorComponent> InteractorComponent;

	virtual void BeginPlay() override;

	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

	void OnInteractableFound(UActorInteractableComponent* FoundActorComponent);
};
