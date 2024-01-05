// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleProject/Game/GeneralGameData.h"
#include "GameFramework/Actor.h"
#include "A_PlaceAccumulationResources.generated.h"


/*
 *  An abstract class that stores common functionality and variables.
 */


UCLASS(Abstract)
class SIMPLEPROJECT_API AA_PlaceAccumulationResources : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AA_PlaceAccumulationResources();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	//A visual game representation of a barn, warehouse, etc.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Settings", meta = (AllowPrivateAccess))
	TSoftObjectPtr<UStaticMeshComponent> VisualGameRepresentation;

	//The maximum capacity of products in units.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Settings", meta = (AllowPrivateAccess))
	int MaxCapacityOfProducts;

};
