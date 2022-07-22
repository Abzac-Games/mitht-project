#include "FirstPersonCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter() : MinFieldOfView(60.0f), MaxFieldOfView(100.0f)
{
	check(MinFieldOfView <= MaxFieldOfView);

	// Set this character to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set defaults for character movement component
	const auto MovementComponent = GetCharacterMovement();
	MovementComponent->NavAgentProps.bCanCrouch = true;
	MovementComponent->MaxWalkSpeed = 200.0f;
	MovementComponent->MaxWalkSpeedCrouched = 100.0f;

	// Set defaults for capsule component
	const auto LocalCapsuleComponent = GetCapsuleComponent();
	LocalCapsuleComponent->SetCapsuleHalfHeight(90.0f);

	// Create and set defaults for camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(LocalCapsuleComponent);
	const FVector CameraRelativeLocation(0, 0, BaseEyeHeight);
	CameraComponent->SetRelativeLocation(CameraRelativeLocation);
	CameraComponent->bUsePawnControlRotation = true;

	// Create and set defaults for interactor component
	InteractorComponent = CreateDefaultSubobject<UActorInteractorComponent>(TEXT("Interactor Component"));
	InteractorComponent->SetUseCustomTraceStart(true);

	// Set up base relative location for crouching
	BaseCameraLocation = CameraRelativeLocation;
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

	// Update camera location for crouching
	const auto NewCameraRelativeLocation =
		FMath::VInterpTo(CurrentInterpolatedCameraLocation, BaseCameraLocation, DeltaTime, 10.0f);
	CurrentInterpolatedCameraLocation = NewCameraRelativeLocation;
	CameraComponent->SetRelativeLocation(NewCameraRelativeLocation);

	// Set new trace start
	const auto NewTraceStart = CameraComponent->GetComponentTransform();
	InteractorComponent->SetCustomTraceStart(NewTraceStart);
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

	// Crouching
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AFirstPersonCharacter::StartCrouching);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AFirstPersonCharacter::StopCrouching);

	// Interactions
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AFirstPersonCharacter::StartInteraction);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &AFirstPersonCharacter::StopInteraction);
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
void AFirstPersonCharacter::ZoomCamera(const float AxisValue)
{
	auto FieldOfView = CameraComponent->FieldOfView;
	FieldOfView = FMath::Clamp(FieldOfView - AxisValue, MinFieldOfView, MaxFieldOfView);
	CameraComponent->SetFieldOfView(FieldOfView);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AFirstPersonCharacter::StartInteraction()
{
	const auto TimeKeyPressed = UGameplayStatics::GetTimeSeconds(this);
	InteractorComponent->OnInteractionKeyPressed.Broadcast(TimeKeyPressed);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AFirstPersonCharacter::StopInteraction()
{
	const auto TimeKeyPressed = UGameplayStatics::GetTimeSeconds(this);
	InteractorComponent->OnInteractionKeyReleased.Broadcast(TimeKeyPressed);
}

void AFirstPersonCharacter::StartCrouching()
{
	Super::Crouch();
}

void AFirstPersonCharacter::StopCrouching()
{
	Super::UnCrouch();
}

void AFirstPersonCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		auto NewLocation = BaseCameraLocation;
		NewLocation.Z += ScaledHalfHeightAdjust;
		CurrentInterpolatedCameraLocation = NewLocation;
	}
}

void AFirstPersonCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		auto NewLocation = BaseCameraLocation;
		NewLocation.Z -= ScaledHalfHeightAdjust;
		CurrentInterpolatedCameraLocation = NewLocation;
	}
}
