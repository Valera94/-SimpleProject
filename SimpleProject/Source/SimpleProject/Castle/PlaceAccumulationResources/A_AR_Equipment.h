// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleProject/Castle/PlaceAccumulationResources/A_PlaceAccumulationResources.h"
#include "A_AR_Equipment.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API AA_AR_Equipment : public AA_PlaceAccumulationResources
{
	GENERATED_BODY()

private:

	//DataResourcesForGame
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "PlayGameInformation", meta = (AllowPrivateAccess))
	FDT_ResourcesInformation DataResourcesEquipment;
};
