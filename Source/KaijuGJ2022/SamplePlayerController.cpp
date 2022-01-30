// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePlayerController.h"

ASamplePlayerController::ASamplePlayerController() {

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASamplePlayerController::BeginPlay() {

    Super::BeginPlay();

    m_pCharacterController = Cast<ACharacterController>(GetCharacter()); // Gets Player Character
    m_pPlayerCamera = Cast<APlayerCamera>(GetPawn()); // Gets Player Camera
}

void ASamplePlayerController::Tick(float DeltaTime) {

}

void ASamplePlayerController::SetupInputComponent() {

    // Always call this.
    Super::SetupInputComponent();

    check(InputComponent);

    if (m_pCharacterController != nullptr) {

        // This is initialized on startup, you can go straight to binding
        InputComponent->BindAxis("MoveFwBw", this, &ASamplePlayerController::CallMoveFwBw);
        InputComponent->BindAxis("MoveRL", this, &ASamplePlayerController::CallMoveRL);
    }

    if (m_pPlayerCamera != nullptr) {

        //CAMERA
        InputComponent->BindAxis("ControllerHorizontalRotation", this, &ASamplePlayerController::CallHorizontalRotate);
        InputComponent->BindAxis("ControllerVerticalRotation", this, &ASamplePlayerController::CallVerticalRotate);

        InputComponent->BindAxis("Zoom", this, &ASamplePlayerController::CallZoom);
    }
}

void ASamplePlayerController::CallMoveFwBw(float value) {

    m_pCharacterController->MoveFwBw(value);
}

void ASamplePlayerController::CallMoveRL(float value) {

    m_pCharacterController->MoveRL(value);
}

void ASamplePlayerController::CallHorizontalRotate(float value) {

    m_pPlayerCamera->HorizontalRotate(value);
}

void ASamplePlayerController::CallVerticalRotate(float value) {

    m_pPlayerCamera->VerticalRotate(value);
}

void ASamplePlayerController::CallZoom(float value) {

    m_pPlayerCamera->Zoom(value);
}
