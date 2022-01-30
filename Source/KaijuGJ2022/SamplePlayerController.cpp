// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePlayerController.h"

ASamplePlayerController::ASamplePlayerController() {

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

}

void ASamplePlayerController::BeginPlay() {

    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterController::StaticClass(), m_pCharacterControllerArray);

    m_pCharacterController = Cast<ACharacterController>(m_pCharacterControllerArray[0]);

    //if (m_pCharacterController == nullptr)
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pCharacterController IS NULL!"));

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCamera::StaticClass(), m_pPlayerCameraArray);

    m_pPlayerCamera = Cast<APlayerCamera>(m_pPlayerCameraArray[0]);

    //if (m_pPlayerCamera == nullptr)
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!"));



    Super::Possess(m_pPlayerCamera);
}

void ASamplePlayerController::Tick(float DeltaTime) {

}

void ASamplePlayerController::SetupInputComponent() {

    // Always call this.
    Super::SetupInputComponent();

    check(InputComponent);

    // This is initialized on startup, you can go straight to binding
    InputComponent->BindAxis("MoveFwBw", this, &ASamplePlayerController::CallMoveFwBw);
    InputComponent->BindAxis("MoveRL", this, &ASamplePlayerController::CallMoveRL);

    //CAMERA
    InputComponent->BindAxis("ControllerHorizontalRotation", this, &ASamplePlayerController::CallHorizontalRotate);
    InputComponent->BindAxis("ControllerVerticalRotation", this, &ASamplePlayerController::CallVerticalRotate);
    InputComponent->BindAxis("MouseHorizontalRotation", this, &ASamplePlayerController::CallHorizontalRotate);
    InputComponent->BindAxis("MouseVerticalRotation", this, &ASamplePlayerController::CallVerticalRotate);

    InputComponent->BindAxis("Zoom", this, &ASamplePlayerController::CallZoom);
}

void ASamplePlayerController::CallMoveFwBw(float value) {

    if (m_pCharacterController != nullptr)
        m_pCharacterController->MoveFwBw(value);
    else
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!"));
}

void ASamplePlayerController::CallMoveRL(float value) {

    if (m_pCharacterController != nullptr)
        m_pCharacterController->MoveRL(value);
    else
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!"));
}

void ASamplePlayerController::CallHorizontalRotate(float value) {

    if (m_pPlayerCamera != nullptr)
        m_pPlayerCamera->HorizontalRotate(value);
}

void ASamplePlayerController::CallVerticalRotate(float value) {

    if (m_pPlayerCamera != nullptr)
        m_pPlayerCamera->VerticalRotate(value);
}

void ASamplePlayerController::CallZoom(float value) {

    if (m_pPlayerCamera != nullptr)
        m_pPlayerCamera->Zoom(value);
}
