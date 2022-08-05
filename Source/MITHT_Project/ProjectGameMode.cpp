#include "ProjectGameMode.h"

#include "FirstPersonCharacter.h"
#include "ProjectHUD.h"
#include "Kismet/GameplayStatics.h"

void AProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		OnPossessedPawnChanged(nullptr, PlayerController->GetPawn());
		PlayerController->OnPossessedPawnChanged.AddDynamic(this, &AProjectGameMode::OnPossessedPawnChanged);
	}
}

void AProjectGameMode::OnPossessedPawnChanged([[maybe_unused]] APawn* OldPawn, APawn* NewPawn)
{
	if (InteractorComponent)
	{
		InteractorComponent->OnInteractableFound.RemoveDynamic(this, &AProjectGameMode::OnInteractableFound);
		InteractorComponent->OnInteractableLost.RemoveDynamic(this, &AProjectGameMode::OnInteractableLost);
	}

	UActorInteractorComponent* NewInteractorComponent = nullptr;
	if (const auto FirstPersonCharacter = Cast<AFirstPersonCharacter>(NewPawn))
	{
		NewInteractorComponent = FirstPersonCharacter->GetInteractorComponent();
	}

	InteractorComponent = NewInteractorComponent;
	if (InteractorComponent)
	{
		InteractorComponent->OnInteractableFound.AddDynamic(this, &AProjectGameMode::OnInteractableFound);
		InteractorComponent->OnInteractableLost.AddDynamic(this, &AProjectGameMode::OnInteractableLost);
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef, CppMemberFunctionMayBeConst
void AProjectGameMode::OnInteractableFound(UActorInteractableComponent* FoundActorComponent)
{
	if (FoundActorComponent)
	{
		if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (const auto HUD = Cast<AProjectHUD>(PlayerController->GetHUD()))
			{
				const auto ComponentName = FoundActorComponent->GetInteractionActionTitle();
				HUD->SetComponentName(ComponentName);
			}
		}
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef, CppMemberFunctionMayBeConst
void AProjectGameMode::OnInteractableLost(UActorInteractableComponent* LostActorComponent)
{
	if (LostActorComponent)
	{
		if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (const auto HUD = Cast<AProjectHUD>(PlayerController->GetHUD()))
			{
				HUD->RemoveComponentName();
			}
		}
	}
}
