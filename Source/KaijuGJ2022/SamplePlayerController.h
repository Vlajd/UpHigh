// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCamera.h"
#include "CharacterController.h"
#include "DoorComponent.h"
#include "KeyItem.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PauseMenu.h"
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

	void CallMoveFwBw(float value);
	void CallMoveRL(float value);

	//CAMERA
	void CallHorizontalRotate(float value);
	void CallVerticalRotate(float value);

	void CallZoom(float value);

	
	//Debug Function
	void DebugFunction();

	
	void RotateCharacter();

	void KillPlayer();

	void TryOpenDoor();
	void TryPickUpKey();
	
	float GetCameraYawRotation();

	void PauseGame() { if (m_pCharacterController != nullptr) m_pCharacterController->ShowPauseMenu(); };

	UFUNCTION(BlueprintCallable) void SetPlayerInputFalse() { m_CanPlayerMove = false; }
	UFUNCTION(BlueprintCallable) void SetPlayerInputTrue() { m_CanPlayerMove = true; }
	UFUNCTION(BlueprintCallable) ACharacter* GetCharacterController() { return m_pCharacterController; }

	// returns UseType
	void CallSetIsUsing(int useType) { m_pCharacterController->UFUNCTIONCallSetIsUsing(useType); };
	
	void CallUse();

	UPROPERTY()
	TArray<AActor*> m_pPlayerCameraArray;
	UPROPERTY()
	TArray<AActor*> m_pCharacterControllerArray;
	UPROPERTY()
	APlayerCamera* m_pPlayerCamera;
	UPROPERTY()
	ACharacterController* m_pCharacterController;
	UPROPERTY()
	USceneComponent* m_pPlayerCameraRotationOrigin;
	UPROPERTY()
	TArray<AActor*> m_pDoorArray;
	UPROPERTY()
	TArray<ADoorComponent*> m_pDoorObjectArray;

	// 1 is OpenDoor
	// 2 is PickupKey
	UPROPERTY(BlueprintReadOnly) int m_UseType;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> CameraToGenerate;

	UPROPERTY() bool m_HasKey;
	TArray<AActor*> m_pKeyArray;
	AKeyItem* m_pKey;

	UPROPERTY(VisibleAnywhere, Category = "Script") bool m_CanPlayerMove;
};
