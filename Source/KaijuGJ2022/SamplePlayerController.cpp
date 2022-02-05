// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePlayerController.h"

ASamplePlayerController::ASamplePlayerController() {

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    m_CanPlayerMove = true;
}

void ASamplePlayerController::BeginPlay() {

    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorComponent::StaticClass(), m_pDoorArray);

    for (int i = 0; i < m_pDoorArray.Num(); i++)
    {
        m_pDoorObjectArray.Add(ToRawPtr(Cast<ADoorComponent>(m_pDoorArray[i])));
    }

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterController::StaticClass(), m_pCharacterControllerArray);

    if(!m_pCharacterControllerArray.IsEmpty())
        m_pCharacterController = Cast<ACharacterController>(m_pCharacterControllerArray[0]); // Gets First Found ACharacterController

    if (m_pCharacterController == nullptr)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pCharacterController IS NULL!::BeginPlay"));

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKeyItem::StaticClass(), m_pKeyArray);

    if (!m_pKeyArray.IsEmpty())
        m_pKey = Cast<AKeyItem>(m_pKeyArray[0]);
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Green, TEXT("m_pKeyArray Is Empty"));

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
            RotateCharacter();
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
            RotateCharacter();
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



void ASamplePlayerController::RotateCharacter() {
    if (!m_CanPlayerMove) return;

    if (m_pCharacterController != nullptr) {

        // m_pCharacterController->RotateOnCamera(GetCameraYawRotation());
    }
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("m_pCharacterController || m_pPlayerCameraRotationOrigin IS NULL!::RotateCharacter"));
}

void ASamplePlayerController::KillPlayer() {
    if (!m_CanPlayerMove) return;

    m_pCharacterController->PlayerDeath();
}

void ASamplePlayerController::TryOpenDoor()
{
    if (!m_CanPlayerMove) return;

    for (int i = 0; i < m_pDoorObjectArray.Num(); i++)
    {
        if (m_pDoorObjectArray[i] != nullptr)
        {
            bool canInteract = FVector::Distance(m_pCharacterController->GetActorLocation(), m_pDoorObjectArray[i]->GetActorLocation()) < m_pDoorObjectArray[i]->m_MinDistanceInCm;

            if (!m_pDoorObjectArray[i]->m_NeedsKey && canInteract)
            {
                m_pDoorObjectArray[i]->OnCallDoorAnim();
                CallSetIsUsing(1);
            }
            else if (m_HasKey && canInteract)
            {
                m_pDoorObjectArray[i]->OnCallDoorAnim();
                m_pDoorObjectArray[i]->m_NeedsKey = false;
                m_HasKey = false;
                CallSetIsUsing(1);
            }
        }
        else {
            GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, FString::Printf(TEXT("DoorComponent At Index %i is NULL"), i));
        }
    }
}

void ASamplePlayerController::TryPickUpKey()
{
    if (m_pKey || m_pCharacterController == nullptr)
    {
        if (FVector::Distance(m_pKey->GetActorLocation(), m_pCharacterController->GetActorLocation()) < m_pKey->m_MinDistInCm)
        {
            m_pKey->Destroy();
            m_HasKey = true;
            CallSetIsUsing(2);
        }
    }
}

void ASamplePlayerController::CallUse()
{
    if (!m_CanPlayerMove) return;
    TryOpenDoor();
    TryPickUpKey();
}
