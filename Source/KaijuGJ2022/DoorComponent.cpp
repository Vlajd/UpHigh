// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorComponent.h"

// Sets default values
ADoorComponent::ADoorComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_MinDistanceInCm = 200.0f;
	
	m_IsOpen = false;

	m_NeedsKey = false;
}

// Called when the game starts or when spawned
void ADoorComponent::BeginPlay()
{
	Super::BeginPlay();

	m_IsOpen = false;
}

// Called every frame
void ADoorComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorComponent::OnCallDoorAnim()
{
	m_IsOpen = !m_IsOpen;
	CallDoorAnim();
}
