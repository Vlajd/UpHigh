// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewController.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AViewController::AViewController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AViewController::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OurPlayer = UGameplayStatics::GetPlayerController(this, 0);
	
	OurPlayer->SetViewTarget(ViewActor);
}

// Called every frame
void AViewController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

