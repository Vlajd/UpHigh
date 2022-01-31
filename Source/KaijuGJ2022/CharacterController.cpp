// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	movementSpeed = 1;
	m_RotationToCameraSpeed = 0.5f;
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ACharacterController::MoveFwBw Is Called!"));

	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value * movementSpeed);
	}
}

void ACharacterController::MoveRL(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ACharacterController::MoveFwBw Is Called!"));

	if (value)
	{
		AddMovementInput(GetActorRightVector(), value * movementSpeed);
	}
}

void ACharacterController::RotateOnCamera(float rotation) {

	FRotator currentRotation = GetActorRotation();
	SetActorRotation(FRotator(currentRotation.Pitch, FMath::Lerp(currentRotation.Yaw, rotation, m_RotationToCameraSpeed), currentRotation.Roll))
}
