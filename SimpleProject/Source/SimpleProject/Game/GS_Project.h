// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_Project.generated.h"





/*
 * *This "Enum" controls the camera view.
 */

UENUM(BlueprintType, Category = "Prject|Enum")
enum class ETypeCameraView : uint8
{
	//It is used as a global map of the world. ref "MountAndBlade"
	ETGV_WorldCameraView UMETA(DisplayName = "WorldCameraView"),
	//Overview of the castle boundary. 
	ETGV_CastleView UMETA(DisplayName = "CastleView"),
	//A local overview of a specific location. Like a plot in "Sims".
	ETGV_LocalPlaceView UMETA(DisplayName = "LocalPlaceView"),
};




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
