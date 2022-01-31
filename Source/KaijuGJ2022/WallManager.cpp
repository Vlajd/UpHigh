// Fill out your copyright notice in the Description page of Project Settings.


#include "WallManager.h"

// Sets default values
AWallManager::AWallManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWallManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallManager::WasHit(FHitResult)
{
	//Find out which part of the wall needs to be invisible

	//Change to correct Mesh

}