// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SimpleProject\Game/GeneralGameData.h"
#include "InputActionValue.h"
#include "PC_Project.h"
#include "SimpleProject/Input/InputConfigData.h"
#include "PlayerCamera_Project.generated.h"


/*
 * This class implements control in the game using the camera. This is the main control for the player.
 * This entity stores information about the movement and binding of buttons.
 */

UCLASS(BlueprintType, Blueprintable, Config = Game)
class SIMPLEPROJECT_API APlayerCamera_Project : public APawn
{
	GENERATED_BODY()

private:

	// Sets default values for this pawn's properties
	APlayerCamera_Project();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaSeconds) override;

	

#pragma region /* *Body Component */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS Camera", meta = (AllowPrivateAccess))
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS Camera", meta = (AllowPrivateAccess))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS Camera", meta = (AllowPrivateAccess))
	class UCameraComponent* CameraComponent;

#pragma endregion

#pragma region /* *Logic Input System  */


public:

	//Delegate ChangeStatusClick
	UPROPERTY(BlueprintAssignable)
	FChangeStatusClick ChangeStatusClick;

	UFUNCTION()
	void OnChangeStatusCLick(const EWhatWasPressed& WhatWasPressed, const EClickStatus& ClickStatus) const
	{
		InputConfigData->ChangeStatusInput(WhatWasPressed, ClickStatus);

		ChangeStatusClick.Broadcast(WhatWasPressed, ClickStatus);
	};


	UFUNCTION(BlueprintCallable,Category="PlayerCamera_Project|GetInformation")
	UInputConfigData* GetInputConfigData() { return InputConfigData ;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RTS Camera|Enhanced Input", meta = (AllowPrivateAccess))
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RTS Camera|Enhanced Input", meta = (AllowPrivateAccess))
	class UInputConfigData* InputConfigData;


	// Handle move input
	void IA_MoveWASD(const FInputActionValue& Value);

	// Handle TurnMouse input
	void IA_TurnMouse(const FInputActionValue& Value);

	// Handle MiddleMouse
	void IA_MiddleMouseInput(const FInputActionValue& Value);
	void IA_MiddleMouseTrigger(const FInputActionValue& Value);

	//Handle Wheel Middle Mouse
	void IA_WheelMiddleMouseInput(const FInputActionValue& Value);

	//Handle Wheel Left Mouse
	void IA_LeftClickMouseInput(const FInputActionValue& Value);

	//Handle Wheel Right Mouse
	void IA_RightClickMouseInput(const FInputActionValue& Value);


#pragma endregion

#pragma region /* *Logic Camera System  */


	UFUNCTION()
	void Bind_ChangeTypeCameraView(ETypeCameraView TypeCameraView);

	/*
	 **DeltaSecondScale			= used to adapt to frames per second and its changes.
	 **TargetPercentFromBorder	= Clamp (0.01 , 0.07) trigger to move.
	 **DynamicChangeSpeed		= Used to change the speed depending on the given value, Spring Arm Lenght is usually used.
	*/
	void MoveUseTriggerTheViewportBorders(const float& DeltaSecondScale, const float& DynamicChangeSpeed);

	void ChangeArmLength(const float& DeltaSecond);


	//X = MinSpringArmLength | Y = MaxSpringArmLength.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS Camera|Information|Settings", meta = (AllowPrivateAccess))
	FVector2D SpringArmLengthMinMax;

	//X = MinSpringArmAngle | Y = MaxSpringArmAngle.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS Camera|Information|Settings", meta = (AllowPrivateAccess))
	FVector2D SpringArmAngleMinMax;

	//CurrentTypeCameraView = It is used to control between the camera mode switches and the necessary visual implementation.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RTS Camera|Information|BindDelegate", meta = (AllowPrivateAccess))
	ETypeCameraView CurrentTypeCameraView;

#pragma endregion
};