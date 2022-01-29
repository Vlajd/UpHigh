// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
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
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	private:

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

		bool m_CanRotate;
};
