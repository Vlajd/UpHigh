// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	
		UPROPERTY(EditAnywhere) float movementSpeed;

		void MoveFwBw(float value);
		void MoveRL(float value);

		void RotateOnCamera(float rotation);

		void RotateMesh();

		void PlayerDeath();

		FRotator GetCurrentRotation() const;

		UPROPERTY(EditAnywhere, Category = "Script") float m_RotationToCameraSpeed;
		UPROPERTY(EditAnywhere, Category = "Script") FVector m_SpawnCoords;
		UPROPERTY(EditAnywhere, Category = "Script") float m_SummonRate;

		USkeletalMeshComponent* m_pMesh;

		UCharacterMovementComponent* m_CharacterMovementComponent;

		float m_PointDirX;
		float m_PointDirY;

		bool m_CanMove;

		//Animation Variables
		float m_Timer;
		bool m_IsSummoning;
		bool m_SummonAnimBool;
		bool m_HasDied;
};
