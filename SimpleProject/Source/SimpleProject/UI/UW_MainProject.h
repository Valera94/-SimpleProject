// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainProject.generated.h"

/**
 * The main game widget that links all the game UI mechanics and widgets in this project.
 */

UCLASS()
class SIMPLEPROJECT_API UUW_MainProject : public UUserWidget
{
	GENERATED_BODY()


	


#pragma region /* *Castle Button */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* CastleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UCanvasPanel* CanvasCastle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* CastleHumanButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* DefendCastleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* CastleProductionButton;

#pragma endregion
};
