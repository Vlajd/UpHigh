// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerCameraComponent.h"

// Sets default values
ACPlayerCameraComponent::ACPlayerCameraComponent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACPlayerCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
