// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera_Project.h"

#include "EnhancedInputComponent.h"
#include "SimpleProject\Input\InputConfigData.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "InputAction.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleProject/Game/GS_Project.h"



// Sets default values
APlayerCamera_Project::APlayerCamera_Project()
{

	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SetRootComponent(SphereComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-90, 0, 0));
	SpringArm->TargetArmLength = 4000;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 6;
	SpringArm->CameraRotationLagSpeed = 6;
	SpringArm->bDoCollisionTest = false;


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);

}


void APlayerCamera_Project::BeginPlay()
{
	Super::BeginPlay();

	//Bind to change View
	if (AGS_Project* L_GS_Project = Cast<AGS_Project>(GetWorld()->GetGameState()))
	{

		L_GS_Project->DelegateChangeTypeCameraView.AddDynamic(this, &APlayerCamera_Project::Bind_ChangeTypeCameraView);
		L_GS_Project->ChangeTypeCameraView(ETypeCameraView::ETGV_LocalView);
		GetLocalViewingPlayerController()->SetShowMouseCursor(true);

		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetLocalViewingPlayerController(), nullptr, EMouseLockMode::LockAlways, false);
	}
}

void APlayerCamera_Project::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCamera_Project::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveUseTriggerTheViewportBorders(DeltaSeconds, SpringArm->TargetArmLength);
	ChangeArmLength(DeltaSeconds);
}


#pragma region /* *Realisation Input System */

void APlayerCamera_Project::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// *Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// *Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	// *Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// *Get the EnhancedInputComponent
	UEnhancedInputComponent* L_EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// *Bind the actions
	L_EnhancedInputComponent->BindAction(InputConfigData->InputMoveWASD, ETriggerEvent::Triggered, this, &APlayerCamera_Project::IA_MoveWASD);
	L_EnhancedInputComponent->BindAction(InputConfigData->InputMoveWASD, ETriggerEvent::Completed, this, &APlayerCamera_Project::IA_MoveWASD);

	// *Bind Turn Mouse
	L_EnhancedInputComponent->BindAction(InputConfigData->TurnMouse, ETriggerEvent::Triggered, this, &APlayerCamera_Project::IA_TurnMouse);


	// *Middle Mouse Input
	L_EnhancedInputComponent->BindAction(InputConfigData->InputMiddleMouse, ETriggerEvent::Triggered, this, &APlayerCamera_Project::IA_MiddleMouseTrigger);


	L_EnhancedInputComponent->BindAction(InputConfigData->InputMiddleMouse, ETriggerEvent::Started, this, &APlayerCamera_Project::IA_MiddleMouseInput);
	L_EnhancedInputComponent->BindAction(InputConfigData->InputMiddleMouse, ETriggerEvent::Completed, this, &APlayerCamera_Project::IA_MiddleMouseInput);

	// Wheel Middle Mouse
	L_EnhancedInputComponent->BindAction(InputConfigData->WheelMiddleInputMouse, ETriggerEvent::Triggered, this, &APlayerCamera_Project::IA_WheelMiddleMouseInput);
}

void APlayerCamera_Project::IA_MoveWASD(const FInputActionValue& Value)
{
	if (Controller != nullptr && CurrentTypeCameraView != ETypeCameraView::ETGV_Menu)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();

		if (MoveValue != FVector2D::Zero())
		{

			InputConfigData->IsPressedWASDMovement = true;
			AddActorWorldOffset(GetActorForwardVector() * MoveValue.X * SpringArm->TargetArmLength + GetActorRightVector() * MoveValue.Y * SpringArm->TargetArmLength);
		}
		else
		{
			InputConfigData->IsPressedWASDMovement = false;
		}

	}
}

void APlayerCamera_Project::IA_TurnMouse(const FInputActionValue& Value)
{
	if (Controller != nullptr && InputConfigData->IsPressedMiddleMouse == true)
	{

		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.f)
		{
			AddActorWorldRotation(FRotator(0, LookValue.X * -100, 0));
		}

		if (LookValue.Y != 0.f)
		{
			float L_Ptich = FMath::ClampAngle(SpringArm->GetRelativeRotation().Pitch + (LookValue.Y * -100.f), SpringArmAngleMinMax.Y, SpringArmAngleMinMax.X);
			SpringArm->SetRelativeRotation(FRotator(L_Ptich, 0.f, 0.f));


		}
	}
}

void APlayerCamera_Project::IA_MiddleMouseInput(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		InputConfigData->IsPressedMiddleMouse = Value.Get<bool>();

		if (Value.Get<bool>() == true)
		{
			GetLocalViewingPlayerController()->SetShowMouseCursor(false);

			//SetMousePositionToMiddleViewport	
			int32 X, Y;
			GetLocalViewingPlayerController()->GetViewportSize(X, Y);
			GetLocalViewingPlayerController()->SetMouseLocation(X / 2, Y / 2);


		}
		else
		{
			//SetMousePositionToMiddleViewport	
			int32 X, Y;
			GetLocalViewingPlayerController()->GetViewportSize(X, Y);
			GetLocalViewingPlayerController()->SetMouseLocation(X / 2, Y / 2);

			GetLocalViewingPlayerController()->SetShowMouseCursor(true);
		}
	}
}
void APlayerCamera_Project::IA_MiddleMouseTrigger(const FInputActionValue& Value)
{
	//SetMousePositionToMiddleViewport	
	int32 X, Y;
	GetLocalViewingPlayerController()->GetViewportSize(X, Y);
	GetLocalViewingPlayerController()->SetMouseLocation(X / 2, Y / 2);
}

void APlayerCamera_Project::IA_WheelMiddleMouseInput(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{

		const float ChangeValue = Value.Get<float>();

		if (ChangeValue != 0.f)
		{
			//When we first use logic
			if (InputConfigData->TargetArmLength == 0) { InputConfigData->TargetArmLength = SpringArm->TargetArmLength; }


			/*
			 *We use "MapRangeClamp" to dynamically change the value for each rotation change.
			 *This will allow you to make a percentage offset per rotation depending
			 *on the current value of "ArmLenght".
			*/

			//TODO We can change "Divide" to other inforation for smooth change result.
			float Divide = 10.f;
			const float L_ResultMapRange = FMath::GetMappedRangeValueClamped(
				FVector2D(SpringArmLengthMinMax.X, SpringArmLengthMinMax.Y),
				FVector2D(SpringArmLengthMinMax.X / Divide, SpringArmLengthMinMax.Y / Divide),
				SpringArm->TargetArmLength);


			//We get the result for the next step with the changed value
			InputConfigData->TargetArmLength = FMath::Clamp(
				SpringArm->TargetArmLength + ChangeValue * L_ResultMapRange,
				SpringArmLengthMinMax.X, SpringArmLengthMinMax.Y);

		}
	}
}


#pragma endregion


void APlayerCamera_Project::Bind_ChangeTypeCameraView(ETypeCameraView TypeCameraView)
{

	//TODO When we have a clear idea of what we need, we can use "CurveData" to get information about the need for changes.

	switch (TypeCameraView)
	{
	case ETypeCameraView::ETGV_GlobalView:

		SpringArmLengthMinMax = FVector2D(200.f, 8000.f);
		SpringArmAngleMinMax = FVector2D(-25.f, -85.f);
		break;

	case ETypeCameraView::ETGV_MiddleView:

		SpringArmLengthMinMax = FVector2D(200.f, 8000.f);
		SpringArmAngleMinMax = FVector2D(-35.f, -85.f);
		break;

	case ETypeCameraView::ETGV_LocalView:

		SpringArmLengthMinMax = FVector2D(200.f, 8000.f);
		SpringArmAngleMinMax = FVector2D(-35.f, -85.f);
		break;

	}

	//End we have to change Actual Current type camera view 
	CurrentTypeCameraView = TypeCameraView;
}

void APlayerCamera_Project::MoveUseTriggerTheViewportBorders(const float& DeltaSecondScale, const float& DynamicChangeSpeed)
{
	if (InputConfigData->IsPressedWASDMovement == false && CurrentTypeCameraView!=ETypeCameraView::ETGV_Menu)
	{

	/*
	 **DeltaSecondScale			= used to adapt to frames per second and its changes.
	 **DynamicChangeSpeed		= Used to change the speed depending on the given value, SpringArmLength is usually used.
	*/

	//Mouse Position.X < SizeViewport.X 0.05%   "MoveLeft"

		if (UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()).X < UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize().X * 0.003f)
		{
			AddActorLocalOffset(FVector(0.f, DeltaSecondScale * FMath::Max(DynamicChangeSpeed, 1.f) * -2.f, 0.f));
		}
		//Mouse Position.X > SizeViewport.X 0.95% "MoveRight"
		else if (UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()).X > UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize().X * 0.995f)
		{
			AddActorLocalOffset(FVector(0.f, DeltaSecondScale * FMath::Max(DynamicChangeSpeed, 1.f) * 2.f, 0.f));
		}

		//Mouse Position.Y < SizeViewport.X 0.05% "MoveUp"
		if (UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()).Y < UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize().Y * 0.003f)
		{
			AddActorLocalOffset(FVector(DeltaSecondScale * FMath::Max(DynamicChangeSpeed, 1.f) * 2.f, 0.f, 0.f));
		}
		//Mouse Position.Y > SizeViewport.X 0.95% "MoveDown"
		else if (UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()).Y > UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize().Y * 0.995f)
		{
			AddActorLocalOffset(FVector(DeltaSecondScale * FMath::Max(DynamicChangeSpeed, 1.f) * -2.f, 0.f, 0.f));
		}
	}
}

void APlayerCamera_Project::ChangeArmLength(const float& DeltaSecond)
{

	if (InputConfigData->TargetArmLength != 0.f && InputConfigData->TargetArmLength != SpringArm->TargetArmLength)
	{
		SpringArm->TargetArmLength = FMath::InterpEaseInOut(SpringArm->TargetArmLength, InputConfigData->TargetArmLength, DeltaSecond, 0.2f);
	}
}
