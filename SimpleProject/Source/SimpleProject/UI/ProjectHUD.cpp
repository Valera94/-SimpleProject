// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectHUD.h"
#include "SimpleProject/Game/GS_Project.h"
#include "Blueprint/UserWidget.h"

#include "UW_MainProject.h"

void AProjectHUD::BeginPlay()
{
	Super::BeginPlay();

	Cast<AGS_Project>(GetWorld()->GetGameState())->DelegateChangeTypeCameraView.AddDynamic(this, &AProjectHUD::ChangeTypeCameraView);

	if(UW_MainProject)
	{
		CreateWidget(GetWorld(), UW_MainProject)->AddToViewport();
	}
	

	//CreateWidget(GetWorld(), UUW_MainProject::StaticClass())->AddToViewport();
		//UW_MainProject = ;
		//if (UW_MainProject)
		//{
		//	UW_MainProject->AddToViewport();
		//}
	
}

void AProjectHUD::ChangeTypeCameraView(ETypeCameraView SelectNewTypeCamera)
{
	//ToDo Realisation
}
