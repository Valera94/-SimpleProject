// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleCreateBuilding.h"



// Sets default values
ASingleCreateBuilding::ASingleCreateBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASingleCreateBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASingleCreateBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeActorLocation();
}

