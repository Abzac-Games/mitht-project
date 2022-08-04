#include "ProjectGameMode.h"

#include "FirstPersonCharacter.h"
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
	UActorInteractorComponent* NewInteractorComponent = nullptr;
	if (const auto FirstPersonCharacter = Cast<AFirstPersonCharacter>(NewPawn))
	{
		NewInteractorComponent = FirstPersonCharacter->GetInteractorComponent();
	}

	InteractorComponent = NewInteractorComponent;
	if (InteractorComponent)
	{
		InteractorComponent->OnInteractableFound.AddDynamic(this, &AProjectGameMode::OnInteractableFound);
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef, CppMemberFunctionMayBeConst
void AProjectGameMode::OnInteractableFound(UActorInteractableComponent* FoundActorComponent)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hello World"));
	}
	if (FoundActorComponent)
	{
		if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (const auto HUD = PlayerController->GetHUD())
			{
				// todo
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("HUD was found!!!"));
				}
			}
		}
	}
}
