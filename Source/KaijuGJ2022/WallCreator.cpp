// Fill out your copyright notice in the Description page of Project Settings.


#include "WallCreator.h"

// Sets default values
AWallCreator::AWallCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWallCreator::BeginPlay()
{
	Super::BeginPlay();

	//TEST: create one wall manager actor

	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	
	NewObject<UInstancedStaticMeshComponent>(Wall);

	//Instantiate all managers at positions given in some array
	//have new array with references to all the managers
	
	//Get Reference to the Camera and to the Player
}

// Called every frame
void AWallCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get current player and camera position

	//calculate ray and then "box/sphere cast?"

	//Send hit message to all managers (WasHit(FHitResult))
}

