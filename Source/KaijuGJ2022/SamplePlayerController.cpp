// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePlayerController.h"

ASamplePlayerController::ASamplePlayerController() {

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    m_CanPlayerMove = true;
}

void ASamplePlayerController::BeginPlay() {

    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterController::StaticClass(), m_pCharacterControllerArray);

    if(!m_pCharacterControllerArray.IsEmpty())
        m_pCharacterController = Cast<ACharacterController>(m_pCharacterControllerArray[0]); // Gets First Found ACharacterController

    if (m_pCharacterController == nullptr)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pCharacterController IS NULL!::BeginPlay"));

    m_HasKey = false;

    m_CanPlayerMove = true;
    m_UseType = 0;
}

void ASamplePlayerController::SetupInputComponent() {

    // Always call this.
    Super::SetupInputComponent();

    check(InputComponent);

    // This is initialized on startup, you can go straight to binding
    InputComponent->BindAxis("MoveFwBw", this, &ASamplePlayerController::CallMoveFwBw).bExecuteWhenPaused = false;
    InputComponent->BindAxis("MoveRL", this, &ASamplePlayerController::CallMoveRL).bExecuteWhenPaused = false;
        
    //CAMERA
    InputComponent->BindAxis("HorizontalRotation", this, &ASamplePlayerController::PlayerCameraHorizontalRotation).bExecuteWhenPaused = false;
    InputComponent->BindAxis("VerticalRotation", this, &ASamplePlayerController::PlayerCameraVerticalRotation).bExecuteWhenPaused = false;
    InputComponent->BindAxis("Zoom", this, &ASamplePlayerController::PlayerCameraZoom).bExecuteWhenPaused = false;

    InputComponent->BindAction("DebugButton", IE_Pressed, this, &ASamplePlayerController::DebugFunction).bExecuteWhenPaused = false;
    InputComponent->BindAction("UseButton", IE_Pressed, this, &ASamplePlayerController::CallUse).bExecuteWhenPaused = false;

    //pause game
    InputComponent->BindAction("PauseButton", IE_Pressed, this, &ASamplePlayerController::PauseGame).bExecuteWhenPaused = true;
}

void ASamplePlayerController::CallMoveFwBw(float value) {
    if (!m_CanPlayerMove) return;

    if (m_pCharacterController != nullptr) {

        m_pCharacterController->SetIsMovingFalse();

        if (value) {

            m_pCharacterController->MoveFwBw(value);
            RotateCharacter(m_pCharacterController);
        }
        else return;
    }
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("m_pCharacterController IS NULL!::CallMoveFwBw"));
}

void ASamplePlayerController::CallMoveRL(float value) {
    
    if (!m_CanPlayerMove) return;

    if (m_pCharacterController != nullptr) {

        if (value) {

            m_pCharacterController->MoveRL(value);
            RotateCharacter(m_pCharacterController);
        }
        else return;
    }
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("m_pCharacterController IS NULL!::CallMoveRL"));
}


// DEBUG FUNCTION

void ASamplePlayerController::DebugFunction() {

    m_pCharacterController->PlayerDeath();
}

void ASamplePlayerController::KillPlayer() {
    if (!m_CanPlayerMove) return;

    m_pCharacterController->PlayerDeath();
}

void ASamplePlayerController::CallUse()
{
    if (!m_CanPlayerMove) return;
    TryOpenDoor();
    TryPickUpKey();
}
