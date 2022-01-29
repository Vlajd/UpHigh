// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCameraController.generated.h"

/**
 * 
 */
UCLASS()
class KAIJUGJ2022_API APlayerCameraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerCameraController();


	UPROPERTY(EditAnywhere)
		ACharacter* Player;

	UPROPERTY(EditAnywhere)
		ACharacter* Camera;
};
