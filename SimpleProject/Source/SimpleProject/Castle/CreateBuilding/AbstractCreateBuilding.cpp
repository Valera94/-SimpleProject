// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractCreateBuilding.h"

#include "Engine/StaticMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleProject/Player/PlayerCamera_Project.h"


// Sets default values
AAbstractCreateBuilding::AAbstractCreateBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArm->SetupAttachment(GetRootComponent());
	RootComponent = SpringArm;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.f;
	SpringArm->CameraLagMaxDistance = 300.f;
	SpringArm->TargetArmLength = 0.f;

	SelectedStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("SelectedStaticMesh");
	SelectedStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SelectedStaticMesh->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AAbstractCreateBuilding::BeginPlay()
{
	Super::BeginPlay();

	
	if (APlayerCamera_Project* PlayerCamera_Project = Cast<APlayerCamera_Project>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		InputConfigData = PlayerCamera_Project->GetInputConfigData();
		PlayerCamera_Project->ChangeStatusClick.AddUniqueDynamic(this, &AAbstractCreateBuilding::Bind_ChangeStatusClick);
	}
}

// Called every frame
void AAbstractCreateBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbstractCreateBuilding::ChangeSelectedMesh (UStaticMesh* SelectedMesh) 
{
	SelectedStaticMesh->SetStaticMesh(SelectedMesh);

	PrimaryActorTick.bCanEverTick = true;
}

void AAbstractCreateBuilding::Bind_ChangeStatusClick(const EWhatWasPressed& WhatWasPressed,
	const EClickStatus& ClickStatus)
{
	switch (WhatWasPressed)
	{
	case EWhatWasPressed::WWP_RightClick:
		if(ClickStatus==EClickStatus::CS_Pressed)
		{
			Destroy();
		}
		break;

	case EWhatWasPressed::WWP_MiddleClick:
		if (ClickStatus == EClickStatus::CS_Pressed)
		{
			SetActorHiddenInGame(true);
			SpringArm->bEnableCameraLag = false;
		}
		else
		{
			SetActorHiddenInGame(false);
			SpringArm->bEnableCameraLag = true;
		}
		break;

	case EWhatWasPressed::WWP_LeftClick:
		if (ClickStatus == EClickStatus::CS_Pressed)
		{
			SelectedStaticMesh->SetHiddenInGame(true);
		}
		else
		{
			SelectedStaticMesh->SetHiddenInGame(false);
		}
		break;
	case EWhatWasPressed::WWP_QClick:
		if (ClickStatus == EClickStatus::CS_Pressed)
		{
			SelectedStaticMesh->AddRelativeRotation(FRotator(0.f, 45.f, 0.f));
		}
		break;

	case EWhatWasPressed::WWP_EClick:
		if (ClickStatus == EClickStatus::CS_Pressed)
		{
			SelectedStaticMesh->AddRelativeRotation(FRotator(0.f, -45.f, 0.f));
		}
		break;
	}

}

void AAbstractCreateBuilding::ChangeActorLocation()
{
		FHitResult HitResult;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);
		if (HitResult.IsValidBlockingHit())
		{
			SetActorLocation(FVector(UKismetMathLibrary::GridSnap_Float(HitResult.Location.X, GridStep * 2),
				UKismetMathLibrary::GridSnap_Float(HitResult.Location.Y, GridStep * 2), HitResult.Location.Z));

			
		}

}

