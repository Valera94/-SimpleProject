// Fill out your copyright notice in the Description page of Project Settings.


#include "WallCreator.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleProject/Player/PlayerCamera_Project.h"

void AWallCreator::Bind_ChangeStatusLeftClick(ELeftClickStatus ChangedStatusLeftClick)
{
	Bind_ChangedStatusLeftClick = ChangedStatusLeftClick;
}

// Sets default values
AWallCreator::AWallCreator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ISM_90 = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_90");
	ISM_90->SetupAttachment(GetRootComponent());

	ISM_45 = CreateDefaultSubobject<UInstancedStaticMeshComponent>("ISM_45");
	ISM_45->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AWallCreator::BeginPlay()
{
	Super::BeginPlay();


	//When we create a given actor, we must subscribe them to the necessary player inputs.
	if (APlayerCamera_Project* PlayerCamera_Project = Cast<APlayerCamera_Project>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerCamera_Project->Delegate_ChangedStatusLeftClick.AddUniqueDynamic(this, &AWallCreator::Bind_ChangeStatusLeftClick);
	}

	//AddInstance For Visualisation
	ISM_90->AddInstance(GetActorTransform());
}

// Called every frame
void AWallCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;

	if (StatusWallCreator == EStatusWallCreator::Create)
	{
		switch (Bind_ChangedStatusLeftClick)
		{
		case ELeftClickStatus::LCS_None:

			ChangeActorLocation();

			break;



		case ELeftClickStatus::LCS_PressedLeftClick:

			if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult))
			{
				CreateWall(ISM_90->GetStaticMesh()->GetBounds().BoxExtent.X * 2, GetActorLocation(), FVector(UKismetMathLibrary::GridSnap_Float(HitResult.Location.X, ISM_90->GetStaticMesh()->GetBounds().BoxExtent.X * 2),
					UKismetMathLibrary::GridSnap_Float(HitResult.Location.Y, ISM_90->GetStaticMesh()->GetBounds().BoxExtent.X * 2), HitResult.Location.Z));
			}

			break;



		case ELeftClickStatus::LCS_UnPressedLeftClick:

			PrimaryActorTick.bCanEverTick = false;

			//When we create a given actor, we must subscribe them to the necessary player inputs.
			if (APlayerCamera_Project* PlayerCamera_Project = Cast<APlayerCamera_Project>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
			{
				PlayerCamera_Project->Delegate_ChangedStatusLeftClick.Remove(this, "Bind_ChangeStatusLeftClick");
			}

			break;
		}
	}
	else
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void AWallCreator::ChangeActorLocation()
{
	if (Bind_ChangedStatusLeftClick == ELeftClickStatus::LCS_None)
	{
		FHitResult HitResult;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);
		if (HitResult.IsValidBlockingHit())
		{
			SetActorLocation(FVector(UKismetMathLibrary::GridSnap_Float(HitResult.Location.X, ISM_90->GetStaticMesh()->GetBounds().BoxExtent.X * 2),
				UKismetMathLibrary::GridSnap_Float(HitResult.Location.Y, ISM_90->GetStaticMesh()->GetBounds().BoxExtent.X * 2), HitResult.Location.Z));
		}
	}
}

void AWallCreator::CreateWall(const float& BoundsMesh, const FVector& StartPosition, const FVector& EndPosition)
{
	//ToDo Instead of a simple cleansing, perhaps we could use a more
	//ToDo thoughtful mechanic without recalculating everything all over again,
	//ToDo but simply shifting it to the right amount in the location.

	//ToDo after testing the game, we will be able to understand how much we need to allocate Arr for this task.

	/*
	 * This principle works with two inputs and,
	 * based on their calculation, we obtain a dynamically changing position in "AnglePosition".
	 */

	 /*
	  *  *		*		*		*
	  *
	  *	*		*		*		End
	  *
	  *	*		*		*		* 2Y
	  *
	  *	Start	Middle	* 1X	* 1Y 2X
	  *
	  *
	  *	The "AnglePosition" is formed equally in combination with the main coordinate "Length X == Length Y".
	  */




#pragma region /* *Initialization variable */


	const float L_Hypotenuse = UKismetMathLibrary::Sqrt(UKismetMathLibrary::Square(BoundsMesh) + UKismetMathLibrary::Square(BoundsMesh));

	const FVector2D L_SelectFloatAngle45XY = FVector2D(StartPosition.X - EndPosition.X < 0 ? 40 : -40,
		StartPosition.Y - EndPosition.Y < 0 ? 40 : -40);


	const float L_AbsDistanceX = UKismetMathLibrary::Abs(StartPosition.X - EndPosition.X);
	const float L_AbsDistanceY = UKismetMathLibrary::Abs(StartPosition.Y - EndPosition.Y);

	//variable data for ISM
	TArray<FVector> ArrAngle90, ArrAngle45;
	FRotator RotatorForAngle45;

#pragma endregion

#pragma region /* *Step 1 - calculate the length of right angles with correction for "AnglePosition" and calculate Position */

	FVector L_StepDistanceForCreateNewBlock = FVector::Zero();
	int L_CycleLastIndexAngle90 = 0;

	//If X Num > Y Num
	if (UKismetMathLibrary::Abs(((StartPosition.X - EndPosition.X) / BoundsMesh)) >
		UKismetMathLibrary::Abs(((StartPosition.Y - EndPosition.Y) / BoundsMesh)))
	{
		L_CycleLastIndexAngle90 = UKismetMathLibrary::FFloor((L_AbsDistanceX - L_AbsDistanceY) / BoundsMesh) + 1;

		const float L_AdaptationConstructionDirectionX = StartPosition.X - EndPosition.X < 0 ? 1 : -1;
		L_StepDistanceForCreateNewBlock = FVector(BoundsMesh * L_AdaptationConstructionDirectionX, 0.f, 0.f);
	}
	else
	{
		L_CycleLastIndexAngle90 = UKismetMathLibrary::FFloor((L_AbsDistanceY - L_AbsDistanceX) / BoundsMesh) + 1;

		const float L_AdaptationConstructionDirectionY = StartPosition.Y - EndPosition.Y < 0 ? 1 : -1;
		L_StepDistanceForCreateNewBlock = FVector(0, BoundsMesh * L_AdaptationConstructionDirectionY, 0.f);
	}

	for (int L_IndexAngle90 = 0; L_IndexAngle90 < L_CycleLastIndexAngle90; L_IndexAngle90++)
	{
		ArrAngle90.Add(StartPosition + L_StepDistanceForCreateNewBlock * L_IndexAngle90);
	}


#pragma endregion


#pragma region /* *Step 2 - calculate the length of right angles with correction for "AnglePosition" */

	// if we have not created any direct blocks, then we use the "StartPosition" location.
	// This will allow us to create blocks at 45 degrees.
	const FVector L_StartCreateAnglePosition = ArrAngle90.IsEmpty() ? StartPosition : ArrAngle90.Last(0);

	
	const int L_CycleLenghtAngle45 = UKismetMathLibrary::FFloor(UKismetMathLibrary::Vector_Distance(L_StartCreateAnglePosition, EndPosition) / L_Hypotenuse);
	if (L_CycleLenghtAngle45 != 0)
	{
		
		const float L_FindedLookYawRotate = UKismetMathLibrary::FindLookAtRotation(L_StartCreateAnglePosition, EndPosition).Yaw;
		const float L_AdaptationYawRotateTo45Angle = L_FindedLookYawRotate - (UKismetMathLibrary::GenericPercent_FloatFloat(L_FindedLookYawRotate, 45.f));

		RotatorForAngle45 = FRotator(0.f, L_FindedLookYawRotate, 0.f);

		ArrAngle45.Add(L_StartCreateAnglePosition + (FVector(L_SelectFloatAngle45XY.X, L_SelectFloatAngle45XY.Y, 0.f)));

		for (int L_IndexAngle45 = 1; L_IndexAngle45 < L_CycleLenghtAngle45; L_IndexAngle45++)
		{
			ArrAngle45.Add((UKismetMathLibrary::GetForwardVector(RotatorForAngle45) * L_Hypotenuse + ArrAngle45.Last(0)));
		}



	}
	

#pragma endregion

#pragma region /* *Step 3 - Create Wall */

	ISM_45->ClearInstances();
	ISM_90->ClearInstances();

	if (!ArrAngle90.IsEmpty())
	{
		for (int Index90 = 0; Index90 < ArrAngle90.Num(); Index90++)
		{
			ISM_90->AddInstance(FTransform(FRotator::ZeroRotator, ArrAngle90[Index90], FVector::One()), true);
		}
	};

	if (!ArrAngle45.IsEmpty())
	{
		for (int Index45 = 0; Index45 < ArrAngle45.Num(); Index45++)
		{
			ISM_45->AddInstance(FTransform(RotatorForAngle45, ArrAngle45[Index45], FVector::One()), true);
		}
	};

#pragma endregion

}

