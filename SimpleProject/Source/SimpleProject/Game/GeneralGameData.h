// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "UObject/NoExportTypes.h"
#include "GeneralGameData.generated.h"

/**
 * 
 */

#pragma region /* *GeneralGameData|Enum */

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
#pragma endregion







#pragma region /* *GeneralGameData|DataResources */

//ToDo To display 2D images, we need to use an atlas.

USTRUCT(BlueprintType, Category = "GeneralGameData|DataResources|InformationView")
struct FResourcesInformationView
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Setting")
	FVector2D UVCoordinateForTexture;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Setting")
	TSoftObjectPtr<UStaticMesh> StaticMesh;

};



/*
 *The place of accumulation of resources for different categorizations.
 */

USTRUCT(BlueprintType, Category = "GeneralGameData|DataResources")
struct FDataResourcesFood
{
	GENERATED_BODY()

	//It is necessary to put a pre-prepared material with an atlas texture into this material.
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setting")
	UMaterialInstance* MaterialInstanceFood; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	TArray<FResourcesInformationView> ResourcesInformationView;

};

USTRUCT(BlueprintType, Category = "GeneralGameData|DataResources")
struct FDataResourcesEquipment
{

GENERATED_BODY()

	//It is necessary to put a pre-prepared material with an atlas texture into this material.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	UMaterialInstance* MaterialInstanceWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	TArray<FResourcesInformationView> ResourcesInformationView;
};

USTRUCT(BlueprintType, Category = "GeneralGameData|DataResources")
struct FDataResourcesRest
{
	GENERATED_BODY()

	//It is necessary to put a pre-prepared material with an atlas texture into this material.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	UMaterialInstance* MaterialInstanceRest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	TArray<FResourcesInformationView> ResourcesInformationView;
};
#pragma endregion



namespace ProjectGameplayTags
{
	//building
	SIMPLEPROJECT_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Building_Attack);

	//Squad
	SIMPLEPROJECT_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Squad_Attack);

};

UCLASS()
class SIMPLEPROJECT_API UGeneralGameData : public UObject
{
	GENERATED_BODY()
	
};
