// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//CAMERA//

	m_RotationOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("RotationOrigin"));
	m_RotationOrigin->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	m_RotationOrigin->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Cam->AttachToComponent(m_RotationOrigin, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	m_Cam->SetRelativeLocation(FVector(1000.0f, 0.0f, 0.0f));

	m_ZoomTarget = CreateDefaultSubobject<USceneComponent>(TEXT("ZoomTarget"));
	m_ZoomTarget->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	m_ZoomTarget->SetRelativeTransform(m_Cam->GetRelativeTransform());

	FVector viewDir = m_RotationOrigin->GetRelativeLocation() - m_Cam->GetRelativeLocation();
	m_Cam->SetRelativeRotation(viewDir.Rotation());

	m_MinPitch = -10.0f;
	m_MaxPitch = 30.0f;
	m_ZoomSpeed = 5.0f;
	m_MinZoom = 5.0f;
	m_MaxZoom = 5000.0f;

	//CAMERA//


	movementSpeed = 1;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	//SET m_ZoomTarget LOCATION TO m_Cam LOCATION
	m_ZoomTarget->SetRelativeLocation(m_Cam->GetRelativeLocation());
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CAMERA ZOOM INTERPOLATE
	m_Cam->SetRelativeLocation(FMath::Lerp(m_Cam->GetRelativeLocation(), m_ZoomTarget->GetRelativeLocation(), m_ZoomSpeed * DeltaTime));

}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveFwBw", this, &ACharacterController::MoveFwBw);
	InputComponent->BindAxis("MoveRL", this, &ACharacterController::MoveRL);

	//CAMERA INPUT//

	InputComponent->BindAxis("MouseHorizontalRotation", this, &ACharacterController::MouseHorizontalRotate);
	InputComponent->BindAxis("MouseVerticalRotation", this, &ACharacterController::MouseVerticalRotate);

	InputComponent->BindAxis("ControllerHorizontalRotation", this, &ACharacterController::HorizontalRotate);
	InputComponent->BindAxis("ControllerVerticalRotation", this, &ACharacterController::VerticalRotate);

	InputComponent->BindAxis("MouseButtonRightHold", this, &ACharacterController::SetCanRotate);

	InputComponent->BindAxis("Zoom", this, &ACharacterController::Zoom);

	//CAMERA INPUT//
}

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


/////////////////////////////////////////////////////////////////////
/////CAMERA//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void ACharacterController::MouseHorizontalRotate(float value) {

	if (m_CanRotate) {

		m_RotationOrigin->AddRelativeRotation(FRotator(0.0f, value, 0.0f));
	}
}

void ACharacterController::MouseVerticalRotate(float value) {

	if (m_CanRotate) {

		m_RotationOrigin->SetRelativeRotation(FRotator(FMath::Clamp(value + m_RotationOrigin->GetRelativeRotation().Pitch, m_MinPitch, m_MaxPitch), m_RotationOrigin->GetRelativeRotation().Yaw, 0.0f));
	}
}

void ACharacterController::HorizontalRotate(float value) {

	m_RotationOrigin->AddRelativeRotation(FRotator(0.0f, value, 0.0f));
}

void ACharacterController::VerticalRotate(float value) {

	m_RotationOrigin->SetRelativeRotation(FRotator(FMath::Clamp(value + m_RotationOrigin->GetRelativeRotation().Pitch, m_MinPitch, m_MaxPitch), m_RotationOrigin->GetRelativeRotation().Yaw, 0.0f));
}

void ACharacterController::SetCanRotate(float value) {

	m_CanRotate = (bool)value;
}

void ACharacterController::Zoom(float value) {

	float Target = FMath::Clamp(FVector::Dist(m_RotationOrigin->GetRelativeLocation(), m_ZoomTarget->GetRelativeLocation() + value), m_MinZoom, m_MaxZoom);

	m_ZoomTarget->AddLocalOffset(FVector(Target - FVector::Dist(m_RotationOrigin->GetRelativeLocation(), m_ZoomTarget->GetRelativeLocation()), 0.0f, 0.0f));
}

/////////////////////////////////////////////////////////////////////
/////CAMERA//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////