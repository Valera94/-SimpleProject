// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_WorkingWithResources.generated.h"



// * The resource management process follows the same pattern for each building.
UENUM(BlueprintType, Category = "WorkingWithResources|Enum")
enum class EStageOfWork : uint8
{
	//Fill the building with the necessary amount of resources for further production.
	EOW_Step1_FillingWithResources UMETA(DisplayName = "Step1_FillingWithResources"),

	//The production process is the process of creating/receiving a resource (X units, Y seconds).
	EOW_Step2_ProductionProcess UMETA(DisplayName = "Step2_ProductionProcess"),

	//The process of Transportation to the warehouse - Transfer the created resource to the right place.
	EOW_Step3_ProcessTransportation UMETA(DisplayName = "Step3_ProcessTransportation"),

	//Adding an Effect - Adds an effect.
	EOW_Step4_AddingEffect UMETA(DisplayName = "Step4_AddingEffect"),

	//Return to the workplace - We are returning.
	EOW_Step5_ReturnToWorkplace UMETA(DisplayName = "Step5_ReturnToWorkplace")
};


/*
*	 * The resource management process follows the same pattern for each building.
*
*	Enum EStageOfWork:
*
*	1. "Step1_FillingWithResources" * Filling with resources - Fill the building with the necessary amount of resources for further production.
*	2. "Step2_ProductionProcess" * The production process is the process of creating/receiving a resource (X units, Y seconds).
*	3. "Step3_ProcessTransportation" * The process of Transportation to the warehouse - Transfer the created resource to the right place.
*	4. "Step4_AddingEffect" * Adding an Effect - Adds an effect.
*	5. "Step5_ReturnToWorkplace" * Return to the workplace -We are returning.
*	
*
*	As an example :
*
*	(Example)
*	The tavern.
*	1. You need 2 workers, 2 barrels of hops.
*	2. 1 units in 3 seconds. (Thus we realize the conditionality of implementation)
*	3. (Skip)
*	4. The effect on the castle is "loyalty of residents to the actions of the castle +X".
*	5. (Skip)
*	
*	(Example)
*	Carrier.
*	1. 1 employee is needed, filled luggage (X units).
*	2. Already got.
*	3. We relate.
*	4. (Skip).
*	5. We return.
*	
 */
UCLASS()
class SIMPLEPROJECT_API AA_WorkingWithResources : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_WorkingWithResources();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
