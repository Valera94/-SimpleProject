// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallCreator.generated.h"

UCLASS()
class SIMPLEPROJECT_API AWallCreator : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWallCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable,Category ="WallCreator")
	void CreateWall(const float& BoundsMesh, const FVector& StartPosition, const FVector& EndPosition, TArray<FVector>& ArrAngle90, TArray<FVector>& ArrAngle45, FRotator& RotatorForAngle45);
};
