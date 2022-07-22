#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "ActorInteractionPlugin/Public/Components/ActorInteractorComponent.h"
#include "FirstPersonCharacter.generated.h"

/**
 * First person character of the project.
 */
UCLASS()
class MITHT_PROJECT_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UActorInteractorComponent> InteractorComponent;

	// TODO: replace with value from the settings
	UPROPERTY(EditDefaultsOnly, DisplayName="Minimum Field Of View", Category="Character",
		meta=(ClampMin=5, UIMin=5, ClampMax=87, UIMax=87))
	float MinFieldOfView;

	// TODO: replace with value from the settings
	UPROPERTY(EditDefaultsOnly, DisplayName="Maximum Field Of View", Category="Character",
		meta=(ClampMin=88, UIMin=88, ClampMax=170, UIMax=170))
	float MaxFieldOfView;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForwardBackward(float AxisValue);

	void MoveRightLeft(float AxisValue);

	void LookUpDown(float AxisValue);

	void TurnRightLeft(float AxisValue);

	void ZoomCamera(float AxisValue);

	void StartInteraction();

	void StopInteraction();

	void StartCrouching();

	void StopCrouching();
};
