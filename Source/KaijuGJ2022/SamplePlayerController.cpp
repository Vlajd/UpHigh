// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePlayerController.h"

ASamplePlayerController::ASamplePlayerController() {

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

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


    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCamera::StaticClass(), m_pPlayerCameraArray);

    if (!m_pPlayerCameraArray.IsEmpty())
        m_pPlayerCamera = Cast<APlayerCamera>(m_pPlayerCameraArray[0]); // Gets First Found APlayerCamera

    if (m_pPlayerCamera == nullptr)
    {
        m_pPlayerCamera = NewObject<APlayerCamera>(CameraToGenerate);
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!::BeginPlay"));
    }
    
    if (m_pPlayerCamera != nullptr)
        m_pPlayerCameraRotationOrigin = Cast<USceneComponent>(m_pPlayerCamera->GetDefaultSubobjectByName(TEXT("RotationOrigin")));
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Green, TEXT("m_pPlayerCamera IS NULL!::Get m_pPlayerCameraRotationOrigin"));

    Possess(m_pPlayerCamera);
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

    InputComponent->BindAction("DebugButton", IE_Pressed, this, &ASamplePlayerController::DebugFunction);
    InputComponent->BindAction("UseButton", IE_Pressed, this, &ASamplePlayerController::CallUse);
}

void ASamplePlayerController::CallMoveFwBw(float value) {

    if (m_pCharacterController != nullptr) {
     
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

void ASamplePlayerController::CallHorizontalRotate(float value) {

    if (m_pPlayerCamera != nullptr) {

        if (value) {

            m_pPlayerCamera->HorizontalRotate(value);
        }
        else return;
    }
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!::CallHorizontalRotate"));
}

void ASamplePlayerController::CallVerticalRotate(float value) {

    if (m_pPlayerCamera != nullptr) {

        if (value) {

            m_pPlayerCamera->VerticalRotate(value);
        }
        else return;
    }
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!::CallVerticalRotate"));
}

void ASamplePlayerController::CallZoom(float value) {

    if (m_pPlayerCamera != nullptr) {

        if (value) {

            m_pPlayerCamera->Zoom(value);
        }
        else return;
    }
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!::CallZoom"));
}


// DEBUG FUNCTION

void ASamplePlayerController::DebugFunction() {

    m_pCharacterController->PlayerDeath();
}



void ASamplePlayerController::RotateCharacter() {

    if (m_pCharacterController != nullptr) {

        m_pCharacterController->RotateOnCamera(GetCameraYawRotation());
    }
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("m_pCharacterController || m_pPlayerCameraRotationOrigin IS NULL!::RotateCharacter"));
}

void ASamplePlayerController::KillPlayer() {

    m_pCharacterController->PlayerDeath();
}

void ASamplePlayerController::TryOpenDoor()
{

    
}

float ASamplePlayerController::GetCameraYawRotation() {

    if (m_pPlayerCameraRotationOrigin != nullptr)
        return m_pPlayerCameraRotationOrigin->GetRelativeRotation().Yaw;
    else
        return 0.0f;
}

void ASamplePlayerController::CallUse()
{

    for (int i = 0; i < m_pDoorObjectArray.Num(); i++)
    {
        if (m_pDoorObjectArray[i] != nullptr)
        {
            m_pDoorObjectArray[i]->OnCallDoorAnim(m_pCharacterController);
        }
        else {
            GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, FString::Printf(TEXT("DoorComponent At Index %i is NULL"), i));
        }
    }
}
