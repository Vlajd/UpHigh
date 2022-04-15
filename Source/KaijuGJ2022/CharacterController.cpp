// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_pMesh = GetMesh();

	m_HasDied = false;

	m_CanMove = true;
	
	m_SummonRate = 10.0f;

	movementSpeed = 1.0f;
	m_RotationToCameraSpeed = 0.5f;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	FVector temp = this->GetActorLocation();
	
	m_SpawnCoords.Set(temp.X, temp.Y, temp.Z);
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_HasDied) return;
	
	if (m_Timer <= 1.0f && !m_IsSummoning)
	{

		m_Timer += m_Timer * DeltaTime * m_SummonRate;
		m_pMesh->SetRelativeScale3D(FVector(1.0f - m_Timer));
	}
	else if (m_Timer <= 1.0f && m_IsSummoning && !m_SummonAnimBool)
	{
		m_Timer += m_Timer * DeltaTime * m_SummonRate;
		m_pMesh->SetRelativeScale3D(FVector(m_Timer));
	}
	else if (m_Timer >= 1.0f && m_SummonAnimBool)
	{
		m_IsSummoning = true;
		m_Timer = 0.01f;
		m_SummonAnimBool = false;
		SetActorLocation(m_SpawnCoords);
	}
	else if (!m_SummonAnimBool)
	{
		m_HasDied = false;
		m_IsSummoning = false;
		m_SummonAnimBool = true;
		m_CanMove = true;
		m_pMesh->SetRelativeScale3D(FVector(1.0f));
	}
	else
	{
		m_SummonAnimBool = false;
	}

	// GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Blue, FString::Printf(TEXT("MoveFwBw: %f, %f"), m_PointDirX, m_PointDirY));

}

void ACharacterController::MoveFwBw(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ACharacterController::MoveFwBw Is Called!"));
	
	if (m_CanMove) {
		
		// W (-1) should equal to -180.0f 
		// S (1) should equal to 0.0f
		m_PointDirX = FMath::Clamp<float>(value * 90.0f, -90.0f, 0.0f);

		if (value) {

			AddMovementInput(GetActorForwardVector(), value * movementSpeed);
	
			RotateMesh();

			m_IsMoving = true;
		}
	}
}

void ACharacterController::MoveRL(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ACharacterController::MoveFwBw Is Called!"));
	
	if (m_CanMove) {
		// D (-1) should equal to -90.0f
		// A (1) should equal to 90.0f
		m_PointDirY = FMath::Clamp<float>(value * 90.0f, 90.0f, -90.0f);

		if (value)
		{
			AddMovementInput(GetActorRightVector(), value * movementSpeed);

			RotateMesh();

			m_IsMoving = true;
		}
	}
}

void ACharacterController::RotateOnCamera(float rotation) {

	SetActorRotation(FRotator(GetCurrentRotation().Pitch, FMath::Lerp(GetCurrentRotation().Yaw, rotation, m_RotationToCameraSpeed), GetCurrentRotation().Roll));
}

void ACharacterController::RotateMesh() {

	// GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("PointDir: %f, %f"), m_PointDir.X, m_PointDir.Y));

	m_pMesh->SetRelativeRotation(FRotator(0.0f, m_PointDirX + m_PointDirX - m_PointDirY, 0.0f));

	m_PointDirX = 0.0f;
	m_PointDirY = 0.0f;
}

FRotator ACharacterController::GetCurrentRotation() const {

	return GetActorRotation();
}


void ACharacterController::PlayerDeath() {

	m_Timer = 0.01f;
	m_SummonAnimBool = true;
	m_HasDied = true;
	m_CanMove = false;

	// testval++;
	// GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("PointDir: %i"), testval));
}
