// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraGameMode.h"

APlayerCameraGameMode::APlayerCameraGameMode()
{
	PlayerControllerClass = APlayerCameraController::StaticClass();
}