// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstanceBuildingManager.generated.h"

USTRUCT(BlueprintType,Category="InstanceBuildingManager|Wall")
struct FStructWallInformation
{
	GENERATED_BODY()

	TArray<FVector> LocationForCreate90;
	TArray<FVector> LocationForCreate45;
	FRotator RotationForCreate45;

};


UCLASS()
class SIMPLEPROJECT_API AInstanceBuildingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInstanceBuildingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
