// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractCreateBuilding.h"
#include "WallCreator.generated.h"






UCLASS()
class SIMPLEPROJECT_API AWallCreator : public AAbstractCreateBuilding
{
	GENERATED_BODY()




public:
	// Sets default values for this actor's properties
	AWallCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//A wall that is being built at an angle of 45 degrees.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WallCreator", meta = (AllowPrivateAccess))
	UInstancedStaticMeshComponent* ISM_45;

	//A wall that is being built at an angle of 90 degrees.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WallCreator", meta = (AllowPrivateAccess))
	UInstancedStaticMeshComponent* ISM_90;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UFUNCTION(BlueprintCallable, Category = "WallCreator")
	void CreateWall(const float& BoundsMesh, const FVector& StartPosition, const FVector& EndPosition);



};
