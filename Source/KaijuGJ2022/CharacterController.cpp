// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	movementSpeed = 1;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	InputComponent->BindAxis("MoveFwBw", this, &ACharacterController::MoveFwBw);
//	InputComponent->BindAxis("MoveRL", this, &ACharacterController::MoveRL);
//}

void ACharacterController::MoveFwBw(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value * movementSpeed);
	}
}

void ACharacterController::MoveRL(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value * movementSpeed);
	}
}
