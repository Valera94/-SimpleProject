// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GeneralGameData.h"
#include "GS_Project.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateChangeTypeCameraView, ETypeCameraView, TypeCameraView);


/**
 * Base GameState.
 * Uses global delegates for the game.
 */

UCLASS(BlueprintType,Blueprintable)
class SIMPLEPROJECT_API AGS_Project : public AGameStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FDelegateChangeTypeCameraView DelegateChangeTypeCameraView;

	UFUNCTION(BlueprintCallable, Category = "Project|Delegate")
	void ChangeTypeCameraView(ETypeCameraView SelectNewTypeCamera) const { DelegateChangeTypeCameraView.Broadcast(SelectNewTypeCamera); }

};
