// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MainProject.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void UUW_MainProject::ChangeSelectedModeInformationUI(const EChangeSelectedModeInformation& ChangeSelectedModeInformation)
{
	switch (ChangeSelectedModeInformation)
	{
	case EChangeSelectedModeInformation::CSMI_CloseAll:


		break;

	case EChangeSelectedModeInformation::CSMI_MenuInformation:


		break;

	case EChangeSelectedModeInformation::CSMI_CastleBuildingInformation:

		//Collapsed "CanvasArmy"

		if (CanvasArmy->GetVisibility() != ESlateVisibility::Collapsed)
		{
			CanvasArmy->SetVisibility(ESlateVisibility::Collapsed);
			Border_SwitchCastleBuilding->SetVisibility(ESlateVisibility::Collapsed);
		}



		//ToggleView "CanvasCastleBuilding"

		if (CanvasCastleBuilding->GetVisibility() == ESlateVisibility::Collapsed)
		{
			CanvasCastleBuilding->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CanvasCastleBuilding->SetVisibility(ESlateVisibility::Collapsed);
		}

		break;

	case EChangeSelectedModeInformation::CSMI_ArmyInformation:

		//Collapsed "CanvasCastleBuilding"

		if (CanvasCastleBuilding->GetVisibility() != ESlateVisibility::Collapsed)
		{
			CanvasCastleBuilding->SetVisibility(ESlateVisibility::Collapsed);
		}


		//ToggleView "CanvasArmy"

			if (CanvasArmy->GetVisibility() == ESlateVisibility::Collapsed)
			{
				CanvasArmy->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				CanvasArmy->SetVisibility(ESlateVisibility::Collapsed);
			}
		
		break;

	}

	OldChangeSelectedModeInformation = ChangeSelectedModeInformation;
}

void UUW_MainProject::NativePreConstruct()
{
	Super::NativePreConstruct();



}

void UUW_MainProject::NativeConstruct()
{
	Super::NativeConstruct();

	CanvasCastleBuilding->SetVisibility(ESlateVisibility::Collapsed);
	CanvasArmy->SetVisibility(ESlateVisibility::Collapsed);

	CastleBuildingButton->OnClicked.AddUniqueDynamic(this, &UUW_MainProject::Bind_PressedCastleButton);
	CastleArmyButton->OnClicked.AddUniqueDynamic(this, &UUW_MainProject::Bind_PressedArmyButton);

	CastleHumanButton->OnClicked.AddUniqueDynamic(this,&UUW_MainProject::Bind_ChangeSwitchInformationToHuman);
	DefendCastleButton->OnClicked.AddUniqueDynamic(this, &UUW_MainProject::Bind_ChangeSwitchInformationToDefend);
	CastleProductionButton->OnClicked.AddUniqueDynamic(this, &UUW_MainProject::Bind_ChangeSwitchInformationToProduction);
}

#pragma region /* *BindDelegate */

void UUW_MainProject::Bind_PressedCastleButton()
{
	ChangeSelectedModeInformationUI(EChangeSelectedModeInformation::CSMI_CastleBuildingInformation);
}

void UUW_MainProject::Bind_PressedArmyButton()
{
	ChangeSelectedModeInformationUI(EChangeSelectedModeInformation::CSMI_ArmyInformation);
}

void UUW_MainProject::Bind_ChangeSwitchInformationToDefend()
{
	//Defend
	WidgetSwitcherCastleBuilding->SetActiveWidgetIndex(0);

	if(Border_SwitchCastleBuilding->GetVisibility()==ESlateVisibility::Collapsed)
	{
		Border_SwitchCastleBuilding->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUW_MainProject::Bind_ChangeSwitchInformationToProduction()
{
	//Production
	WidgetSwitcherCastleBuilding->SetActiveWidgetIndex(1);

	if (Border_SwitchCastleBuilding->GetVisibility() == ESlateVisibility::Collapsed)
	{
		Border_SwitchCastleBuilding->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUW_MainProject::Bind_ChangeSwitchInformationToHuman()
{
	//Human
	WidgetSwitcherCastleBuilding->SetActiveWidgetIndex(2);

	if (Border_SwitchCastleBuilding->GetVisibility() == ESlateVisibility::Collapsed)
	{
		Border_SwitchCastleBuilding->SetVisibility(ESlateVisibility::Visible);
	}
}


#pragma endregion
