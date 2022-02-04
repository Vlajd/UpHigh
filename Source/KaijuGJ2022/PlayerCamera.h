// Fill out your copyright notice in the Description page of Project Settings.

//CAMERA SANDBOX, INGAME CAMERA IS CREATED IN CLASS ACharacterController

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "UObject/UObjectGlobals.h"
#include "PlayerCamera.generated.h"

UCLASS() class KAIJUGJ2022_API APlayerCamera : public APawn {

	GENERATED_BODY()

	public:
		// Sets default values for this character's properties
		APlayerCamera();
	
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	
	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;
	
		// Called to bind functionality to input
		//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		void MouseHorizontalRotate(float value);
		void MouseVerticalRotate(float value);
		
		void HorizontalRotate(float value);
		void VerticalRotate(float value);

		void SetCanRotate(float value);

		void Zoom(float value);

		UPROPERTY(EditAnywhere) USceneComponent* m_RotationOrigin;
		UPROPERTY(EditAnywhere) USceneComponent* m_ZoomTarget;
		UPROPERTY(EditAnywhere, Category = "Camera") UCameraComponent* m_Cam;
		UPROPERTY(EditAnywhere, Category = "Script") float m_MinPitch;
		UPROPERTY(EditAnywhere, Category = "Script") float m_MaxPitch;
		UPROPERTY(EditAnywhere, Category = "Script") float m_MinZoom;
		UPROPERTY(EditAnywhere, Category = "Script") float m_MaxZoom;
		UPROPERTY(EditAnywhere, Category = "Script") float m_ZoomSpeed;
		UPROPERTY(EditAnywhere, Category = "Script") FVector m_SpawnLocation;

		bool m_CanRotate;
		//FObjectInitializer* m_pObjectInitializer;
};
