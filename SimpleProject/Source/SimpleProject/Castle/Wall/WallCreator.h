// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallCreator.generated.h"


enum class ELeftClickStatus : uint8;

UENUM(BlueprintType, Category = "WallCreator")
enum class EStatusWallCreator :uint8
{
	Ready,
	Create,
};

UCLASS()
class SIMPLEPROJECT_API AWallCreator : public AActor
{
	GENERATED_BODY()

#pragma region /* *BindDelegate  */

	UFUNCTION()
	void Bind_ChangeStatusLeftClick(ELeftClickStatus ChangedStatusLeftClick);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WallCreator|InformationAboutClick", meta = (AllowPrivateAccess))
	ELeftClickStatus Bind_ChangedStatusLeftClick;

	UPROPERTY(BlueprintReadOnly, Category = "WallCreator|InformationAboutClick", meta = (AllowPrivateAccess, ExposeOnSpawn))
	EStatusWallCreator StatusWallCreator = EStatusWallCreator::Ready;

#pragma endregion


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
	void ChangeActorLocation();

	UFUNCTION(BlueprintCallable, Category = "WallCreator")
	void CreateWall(const float& BoundsMesh, const FVector& StartPosition, const FVector& EndPosition);



};
