// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMesh = GetMesh();

	m_HasDied = false;

	m_SummonRate = 10.0f;

	m_SpawnCoords.Set(0.0f, 0.0f, 0.0f);

	movementSpeed = 1.0f;
	m_RotationToCameraSpeed = 0.5f;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(m_SpawnCoords);
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_HasDied) {

		if (m_Timer <= 1.0f && !m_IsSummoning) {
	
			m_Timer += m_Timer * DeltaTime * m_SummonRate;
			m_pMesh->SetRelativeScale3D(FVector(1.0f - m_Timer));
		}
		else if (m_Timer <= 1.0f && m_IsSummoning && !m_SummonAnimBool) {

			m_Timer += m_Timer * DeltaTime * m_SummonRate;
			m_pMesh->SetRelativeScale3D(FVector(m_Timer));
		}
		else if (m_Timer >= 1.0f && m_SummonAnimBool) {

			m_IsSummoning = true;
			m_Timer = 0.01f;
			m_SummonAnimBool = false;
			SetActorLocation(m_SpawnCoords);
		}
		else if (!m_SummonAnimBool) {

			m_HasDied = false;
			m_IsSummoning = false;
			m_SummonAnimBool = true;
		}
		else {

			m_SummonAnimBool = false;
		}

	}
}

void ACharacterController::MoveFwBw(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ACharacterController::MoveFwBw Is Called!"));


	// W (-1) should equal to -180.0f 
	// S (1) should equal to 0.0f 
	m_PointDir.Set(FMath::Clamp<float>(value * 180.0f, -180.0f, 0.0f), m_PointDir.Y);

	// this does not get executed currently for some reason:
	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Blue, FString::Printf(TEXT("MoveFwBw: %f, %f"), m_PointDir.X, m_PointDir.Y));

	if (value) {

		AddMovementInput(GetActorForwardVector(), value * movementSpeed);
	
		RotateMesh();
	}
}

void ACharacterController::MoveRL(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ACharacterController::MoveFwBw Is Called!"));

	// D (-1) should equal to -90.0f
	// A (1) should equal to 90.0f
	m_PointDir.Set(m_PointDir.X, FMath::Clamp<float>(value * 90.0f, -90.0f, 90.0f));

	// this does not get executed currently for some reason:
	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Blue, FString::Printf(TEXT("MoveRL: %f, %f"), m_PointDir.X, m_PointDir.Y));


	if (value)
	{
		AddMovementInput(GetActorRightVector(), value * movementSpeed);

		RotateMesh();
	}
}

void ACharacterController::RotateOnCamera(float rotation) {

	SetActorRotation(FRotator(GetCurrentRotation().Pitch, FMath::Lerp(GetCurrentRotation().Yaw, rotation, m_RotationToCameraSpeed), GetCurrentRotation().Roll));
}

void ACharacterController::RotateMesh() {

	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("PointDir: %f, %f"), m_PointDir.X, m_PointDir.Y));

	m_pMesh->SetRelativeRotation(FRotator(0.0f, m_PointDir.X + m_PointDir.Y, 0.0f));

	m_PointDir.Set(0.0f, 0.0f);
}

FRotator ACharacterController::GetCurrentRotation() {

	return GetActorRotation();
}

void ACharacterController::PlayerDeath() {

	m_Timer = 0.01f;
	m_SummonAnimBool = true;
	m_HasDied = true;
}
