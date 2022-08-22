#include "EquipmentComponent.h"

AEquipmentComponent::AEquipmentComponent()
{
	PrimaryActorTick.bCanEverTick = true;

	Interactable = CreateDefaultSubobject<UActorInteractableComponent>(TEXT("Interactable"));
	Interactable->SetInteractionType(EInteractableType::EIT_Press);
	Interactable->SetInteractionCooldownTime(0.0f);
	Interactable->SetInteractableWidgetClass(nullptr);
	Interactable->SetInteractionActionTitle(FText::GetEmpty());
	Interactable->SetInteractionActionText(FText::GetEmpty());
	Interactable->SetInteractionActionKey(FText::GetEmpty());

	StateMachine = CreateDefaultSubobject<USMStateMachineComponent>(TEXT("State Machine"));
	StateMachine->bStartOnBeginPlay = true;
	StateMachine->bStopOnEndPlay = true;
}
