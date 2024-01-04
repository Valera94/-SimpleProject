// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/WidgetSwitcher.h"
#include "UW_MainProject.generated.h"

UENUM(BlueprintType, Category = "UWMainProject|Enum")
enum class EChangeSelectedModeInformation : uint8
{
	CSMI_CloseAll UMETA(DisplayName = "CloseAll"),
	CSMI_MenuInformation UMETA(DisplayName = "MenuInformation"),
	CSMI_CastleBuildingInformation UMETA(DisplayName = "CastleInformation"),
	CSMI_ArmyInformation UMETA(DisplayName = "ArmyInformation")
	
};

/**
 * The main game widget that links all the game UI mechanics and widgets in this project.
 */

UCLASS()
class SIMPLEPROJECT_API UUW_MainProject : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category ="UWMainProject")
	void ChangeSelectedModeInformationUI(const EChangeSelectedModeInformation& ChangeSelectedModeInformation);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

#pragma region /* *BindDelegate */

	UFUNCTION()
	void Bind_PressedCastleButton();
	UFUNCTION()
	void Bind_PressedArmyButton();


UFUNCTION()
void Bind_ChangeSwitchInformationToDefend();

UFUNCTION()
void Bind_ChangeSwitchInformationToProduction();

UFUNCTION()
void Bind_ChangeSwitchInformationToHuman();
#pragma endregion




protected:

	UPROPERTY(BlueprintReadOnly, Category ="UWMainProject",meta=(AllowPrivateAccess))
	EChangeSelectedModeInformation OldChangeSelectedModeInformation;


#pragma region /* *Castle Button */

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* CastleBuildingButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UCanvasPanel* CanvasCastleBuilding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* CastleHumanButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* DefendCastleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* CastleProductionButton;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UBorder* Border_SwitchCastleBuilding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UWidgetSwitcher* WidgetSwitcherCastleBuilding;
#pragma endregion



#pragma region /* *Castle Army */

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UButton* CastleArmyButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CPP|CastleButton", meta = (BindWidget, AllowPrivateAccess))
	class UCanvasPanel* CanvasArmy;

#pragma endregion
};
