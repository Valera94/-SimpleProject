// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleProject\Game/GeneralGameData.h"
#include "GameFramework/HUD.h"
#include "ProjectHUD.generated.h"

class UUW_MainProject;

/**
 * 
 */
UCLASS()
class SIMPLEPROJECT_API AProjectHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

#pragma region /* *BindDelegate */

	UFUNCTION()
	void ChangeTypeCameraView(ETypeCameraView SelectNewTypeCamera);

#pragma endregion

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="HUDProject|CreateClass",meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> UW_MainProject;
};
