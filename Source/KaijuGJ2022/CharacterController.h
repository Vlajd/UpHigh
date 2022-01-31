// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "kismet/GameplayStatics.h"
#include "CharacterController.generated.h"

UCLASS() class KAIJUGJ2022_API ACharacterController : public ACharacter {

	GENERATED_BODY()

	public:
		// Sets default values for this character's properties
		ACharacterController();
	
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	
	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;
	
		// Called to bind functionality to input
		//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
		UPROPERTY(EditAnywhere) float movementSpeed;

		void MoveFwBw(float value);
		void MoveRL(float value);

		void RotateOnCamera(float rotation);

		UPROPERTY(EditAnywhere, Category = "Script") float m_RotationToCameraSpeed;

};
