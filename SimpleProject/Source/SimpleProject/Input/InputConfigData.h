// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "InputConfigData.generated.h"

/**
 * Store pointer to Input Action for native binding
*/
UCLASS()
class SIMPLEPROJECT_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMoveWASD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* TurnMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMiddleMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* WheelMiddleInputMouse;



	//ToDo we can replace location this variable if its need

	bool IsPressedMiddleMouse = false;
	bool IsPressedWASDMovement = false;
	float TargetArmLength = 0.f;
};
