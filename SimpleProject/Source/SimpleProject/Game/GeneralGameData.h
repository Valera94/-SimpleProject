// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GeneralGameData.generated.h"

/**
 * 
 */


 /*
  * *This "Enum" controls the camera view.
  */

UENUM(BlueprintType, Category = "GeneralGameData|Enum")
enum class ETypeCameraView : uint8
{
	//ToDo Change after understanding the naming

	//It is used as a global map of the world. ref "MountAndBlade"
	ETGV_GlobalView UMETA(DisplayName = "GlobalView"),
	//Overview of the castle boundary. 
	ETGV_MiddleView UMETA(DisplayName = "MiddleView"),
	//A local overview of a specific location. Like a plot in "Sims".
	ETGV_LocalView UMETA(DisplayName = "LocalView"),
};



UCLASS()
class SIMPLEPROJECT_API UGeneralGameData : public UObject
{
	GENERATED_BODY()
	
};
