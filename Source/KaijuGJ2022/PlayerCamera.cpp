// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"

// Sets default values
APlayerCamera::APlayerCamera() {

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	m_RotationOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("RotationOrigin"));
	m_RotationOrigin->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	m_RotationOrigin->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Cam->AttachToComponent(m_RotationOrigin, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	m_Cam->SetRelativeLocation(FVector(1000.0f, 0.0f, 0.0f));

	FVector viewDir = m_RotationOrigin->GetRelativeLocation() - m_Cam->GetRelativeLocation();
	m_Cam->SetRelativeRotation(viewDir.Rotation());

	m_MinPitch = -10.0f;
	m_MaxPitch = 30.0f;
}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay() {

	Super::BeginPlay();

}

// Called every frame
void APlayerCamera::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MouseHorizontalRotation", this, &APlayerCamera::MouseHorizontalRotate);
	InputComponent->BindAxis("MouseVerticalRotation", this, &APlayerCamera::MouseVerticalRotate);

	InputComponent->BindAxis("ControllerHorizontalRotation", this, &APlayerCamera::HorizontalRotate);
	InputComponent->BindAxis("ControllerVerticalRotation", this, &APlayerCamera::VerticalRotate);

	InputComponent->BindAxis("MouseButtonRightHold", this, &APlayerCamera::SetCanRotate);
}

void APlayerCamera::MouseHorizontalRotate(float value) {

	if (m_CanRotate) {

		m_RotationOrigin->AddRelativeRotation(FRotator(0.0f, value, 0.0f));
	}
}

void APlayerCamera::MouseVerticalRotate(float value) {

	if (m_CanRotate) {

		m_RotationOrigin->SetRelativeRotation(FRotator(FMath::Clamp(value + m_RotationOrigin->GetRelativeRotation().Pitch, m_MinPitch, m_MaxPitch), m_RotationOrigin->GetRelativeRotation().Yaw, 0.0f));
	}
}

void APlayerCamera::HorizontalRotate(float value) {

	m_RotationOrigin->AddRelativeRotation(FRotator(0.0f, value, 0.0f));
}

void APlayerCamera::VerticalRotate(float value) {

	m_RotationOrigin->SetRelativeRotation(FRotator(FMath::Clamp(value + m_RotationOrigin->GetRelativeRotation().Pitch, m_MinPitch, m_MaxPitch), m_RotationOrigin->GetRelativeRotation().Yaw, 0.0f));
}

void APlayerCamera::SetCanRotate(float value) {

	m_CanRotate = (bool)value;
}