// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceBuildingManager.h"

// Sets default values
AInstanceBuildingManager::AInstanceBuildingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInstanceBuildingManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInstanceBuildingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
