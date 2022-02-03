// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePlayerController.h"

ASamplePlayerController::ASamplePlayerController() {

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    m_IsGamePaused = false;
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

    /*if (m_pPlayerCamera == nullptr)
    {
        m_pPlayerCamera = NewObject<APlayerCamera>(CameraToGenerate);
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("m_pPlayerCamera IS NULL!::BeginPlay"));
    }*/
    
    if (m_pPlayerCamera != nullptr)
        m_pPlayerCameraRotationOrigin = Cast<USceneComponent>(m_pPlayerCamera->GetDefaultSubobjectByName(TEXT("RotationOrigin")));
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Green, TEXT("m_pPlayerCamera IS NULL!::Get m_pPlayerCameraRotationOrigin"));

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKeyItem::StaticClass(), m_pKeyArray);

    if (!m_pKeyArray.IsEmpty())
        m_pKey = Cast<AKeyItem>(m_pKeyArray[0]);
    else
        GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Green, TEXT("m_pKeyArray Is Empty"));

    m_HasKey = false;
    m_IsGamePaused = false;

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
    InputComponent->BindAction("PauseButton", IE_Pressed, this, &ASamplePlayerController::PauseGame);
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
    for (int i = 0; i < m_pDoorObjectArray.Num(); i++)
    {
        if (m_pDoorObjectArray[i] != nullptr)
        {
            if (!m_pDoorObjectArray[i]->m_NeedsKey) {
                m_pDoorObjectArray[i]->OnCallDoorAnim(m_pCharacterController);
            }
            else if (m_HasKey)
            {
                m_pDoorObjectArray[i]->OnCallDoorAnim(m_pCharacterController);
                m_pDoorObjectArray[i]->m_NeedsKey = false;
                m_HasKey = false;
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
        }
    }
}

float ASamplePlayerController::GetCameraYawRotation() {

    if (m_pPlayerCameraRotationOrigin != nullptr)
        return m_pPlayerCameraRotationOrigin->GetRelativeRotation().Yaw;
    else
        return 0.0f;
}

void ASamplePlayerController::PauseGame()
{
    m_IsGamePaused = !m_IsGamePaused;

    FInputModeGameAndUI Mode;
    
    if(!m_IsGamePaused)
    {
        m_PauseMenu = CreateWidget<UPauseMenu>(this, UPauseMenu::StaticClass());
        Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        Mode.SetHideCursorDuringCapture(false);
        SetInputMode(Mode);
        m_PauseMenu->AddToViewport(9999);
    }
    else
    {
        m_PauseMenu->Destruct();
        Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
        Mode.SetHideCursorDuringCapture(true);
        SetInputMode(Mode);
    }
}

void ASamplePlayerController::CallUse()
{
    TryOpenDoor();
    TryPickUpKey();
}
