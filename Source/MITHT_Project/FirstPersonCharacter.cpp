#include "FirstPersonCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter() : MinFieldOfView(60.0f), MaxFieldOfView(100.0f)
{
	check(MinFieldOfView <= MaxFieldOfView);

	// Set this character to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set defaults for capsule component
	const auto LocalCapsuleComponent = GetCapsuleComponent();
	LocalCapsuleComponent->SetCapsuleHalfHeight(90.0f);

	// Create and set defaults for camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(LocalCapsuleComponent);
	const FVector RelativeLocation(0, 0, BaseEyeHeight);
	CameraComponent->SetRelativeLocation(RelativeLocation);
	CameraComponent->bUsePawnControlRotation = true;

	// Create and set defaults for interactor component
	InteractorComponent = CreateDefaultSubobject<UActorInteractorComponent>(TEXT("Interactor Component"));
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFirstPersonCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Character movement
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &AFirstPersonCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &AFirstPersonCharacter::MoveRightLeft);

	// Camera manipulation
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left"), this, &AFirstPersonCharacter::TurnRightLeft);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down"), this, &AFirstPersonCharacter::LookUpDown);
	PlayerInputComponent->BindAxis(TEXT("Zoom Camera"), this, &AFirstPersonCharacter::ZoomCamera);

	// Interactions
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AFirstPersonCharacter::InteractionPressed);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &AFirstPersonCharacter::InteractionReleased);
}

void AFirstPersonCharacter::MoveForwardBackward(const float AxisValue)
{
	const auto Direction = GetActorForwardVector() * AxisValue;
	AddMovementInput(Direction);
}

void AFirstPersonCharacter::MoveRightLeft(const float AxisValue)
{
	const auto Direction = GetActorRightVector() * AxisValue;
	AddMovementInput(Direction);
}

void AFirstPersonCharacter::LookUpDown(const float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AFirstPersonCharacter::TurnRightLeft(const float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AFirstPersonCharacter::InteractionPressed()
{
	const auto TimeKeyPressed = UGameplayStatics::GetTimeSeconds(this);
	InteractorComponent->OnInteractionKeyPressed.Broadcast(TimeKeyPressed);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AFirstPersonCharacter::InteractionReleased()
{
	const auto TimeKeyPressed = UGameplayStatics::GetTimeSeconds(this);
	InteractorComponent->OnInteractionKeyReleased.Broadcast(TimeKeyPressed);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AFirstPersonCharacter::ZoomCamera(const float AxisValue)
{
	auto FieldOfView = CameraComponent->FieldOfView;
	FieldOfView = FMath::Clamp(FieldOfView - AxisValue, MinFieldOfView, MaxFieldOfView);
	CameraComponent->SetFieldOfView(FieldOfView);
}
