// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"

// Sets default values
APlayerCamera::APlayerCamera() {

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	m_MinPitch = 0.0f;
	m_MaxPitch = 40.0f;
	m_ZoomSpeed = 5.0f;
	m_MinZoom = 5.0f;
	m_MaxZoom = 5000.0f;
	m_SpawnLocation.Set(0.0f, 0.0f, 80.0f);
}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay() {

	Super::BeginPlay();

	SetActorLocation(m_SpawnLocation);
	m_ZoomTarget->SetRelativeLocation(m_Cam->GetRelativeLocation());
}

// Called every frame
void APlayerCamera::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	m_Cam->SetRelativeLocation(FMath::Lerp(m_Cam->GetRelativeLocation(), m_ZoomTarget->GetRelativeLocation(), m_ZoomSpeed * DeltaTime));
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

void APlayerCamera::Zoom(float value) {

	float Target = FMath::Clamp(FVector::Dist(m_RotationOrigin->GetRelativeLocation(), m_ZoomTarget->GetRelativeLocation() + value), m_MinZoom, m_MaxZoom);

	m_ZoomTarget->AddLocalOffset(FVector(Target - FVector::Dist(m_RotationOrigin->GetRelativeLocation(), m_ZoomTarget->GetRelativeLocation()), 0.0f, 0.0f));
}
