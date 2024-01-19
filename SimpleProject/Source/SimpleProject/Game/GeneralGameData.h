// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "UObject/NoExportTypes.h"
#include "GeneralGameData.generated.h"


#pragma region /* *GeneralGameData|Enum */

 /*
  * *This "Enum" controls the camera view.
  */

UENUM(BlueprintType)
enum class ETypeCameraView : uint8
{
	//ToDo Change after understanding the naming

	//It is used as a Menu.
	ETGV_Menu UMETA(DisplayName = "Menu"),
	//It is used as a global map of the world. ref "MountAndBlade"
	ETGV_GlobalView UMETA(DisplayName = "GlobalView"),
	//Overview of the castle boundary. 
	ETGV_MiddleView UMETA(DisplayName = "MiddleView"),
	//A local overview of a specific location. Like a plot in "Sims".
	ETGV_LocalView UMETA(DisplayName = "LocalView"),
};
#pragma endregion







#pragma region /* *GeneralGameData */


//It is used for visual representation of both the world and UI/UX.
USTRUCT(BlueprintType)
struct FStruct_Information
{
	GENERATED_BODY()

public:

	//To display 2D images, we need to use an atlas.
	//It is necessary to put a pre-prepared material with an atlas texture into this material.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Texture")
	TSoftObjectPtr<UMaterialInstance> MaterialInstance;

	//Use together with "MaterialInstance" as a result it will give a "2D Image"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Texture")
	FVector2D UVCoordinateForTexture;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|WorldPresentation")
	TSoftObjectPtr<UStaticMesh> WorldPresentationMesh;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Description")
	FText ShortText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting|Description")
	FText LongText;

};

//*************************************************************

USTRUCT(BlueprintType)
struct FDT_ResourcesInformation : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStruct_Information ResourcesInformation;
};

//*************************************************************



/*
 * It is included in the structure for a possible upgrade of resources,
 * taking into account related areas. Sword + Oil. Axe + Fire particles.
 * In this way, you can combine completely interesting possibilities of combinations.
 */

USTRUCT(BlueprintType)
struct FStruct_InvestAndReceiveResources
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DTResources;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DataTableRow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmountResources;
};

//*************************************************************

/*
 *The structure for the visual representation of the building
 *and additional information with the production.
 */

USTRUCT(BlueprintType)
struct FStruct_IndustryBuilding
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneralGameData|InformationView")
	FStruct_Information InformationBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneralGameData|Worker")
	int32 AmountWorker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneralGameData|ResourcesForProduction")
	TArray<FStruct_InvestAndReceiveResources> ResourcesForProduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneralGameData|ResourcesForProduction")
	TArray <FStruct_InvestAndReceiveResources> ResourcesProduced;

};


USTRUCT(BlueprintType, Category = "GeneralGameData")
struct FDT_IndustryBuilding : public FTableRowBase
{
	GENERATED_BODY()

public:
	//Arr used how Level Build
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStruct_IndustryBuilding> LevelIndustryBuilding;
};
#pragma endregion




//GameplayTag

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
