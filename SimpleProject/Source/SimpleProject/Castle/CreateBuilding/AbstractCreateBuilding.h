// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleProject/Input/InputConfigData.h"
#include "AbstractCreateBuilding.generated.h"

enum class ELeftClickStatus : uint8;


UENUM(BlueprintType, Category = "StageBuilding")
enum class EStatusBuilding :uint8
{
	SB_StagePlanning	UMETA(DisplayName = "Stage Planning"),
	SB_StageBuild		UMETA(DisplayName = "Stage Build"),
	SB_StageComplete	UMETA(DisplayName = "Stage Complete")
};


UCLASS(Abstract)
class SIMPLEPROJECT_API AAbstractCreateBuilding : public AActor
{
	GENERATED_BODY()

protected:


public:
	// Sets default values for this actor's properties
	AAbstractCreateBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CreateBuilding")
	void ChangeSelectedMesh(UStaticMesh* SelectedMesh);

protected:

	//SelectedStaticMesh from UI
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category = "Components",meta=(AllowPrivateAccess))
	UStaticMeshComponent* SelectedStaticMesh;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	UInputConfigData* InputConfigData;


	UFUNCTION()
	virtual void Bind_ChangeStatusClick(const EWhatWasPressed& WhatWasPressed, const EClickStatus& ClickStatus);

	UFUNCTION(BlueprintCallable, Category = "CreateBuilding")
	void ChangeActorLocation();


	//Value, for GridLocation.
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float GridStep= 20.f;



};
