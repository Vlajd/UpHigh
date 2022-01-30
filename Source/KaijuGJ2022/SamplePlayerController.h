// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCamera.h"
#include "CharacterController.h"
#include "SamplePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KAIJUGJ2022_API ASamplePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		ASamplePlayerController();

	protected:
		virtual void BeginPlay() override;

	public:
		virtual void Tick(float DeltaTime) override;

		virtual void SetupInputComponent() override;

		virtual void CallMoveFwBw(float value);
		virtual void CallMoveRL(float value);

		//CAMERA
		virtual void CallHorizontalRotate(float value);
		virtual void CallVerticalRotate(float value);

		virtual void CallZoom(float value);

		UPROPERTY(Transient, EditAnywhere) APlayerCamera* m_pPlayerCamera;
		UPROPERTY(Transient, EditAnywhere) ACharacterController* m_pCharacterController;
};
