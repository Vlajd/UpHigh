// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.h"
#include "DoorComponent.h"
#include "KeyItem.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PauseMenu.h"
#include "CPlayerCameraComponent.h"
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

	virtual void SetupInputComponent() override;

	void CallMoveFwBw(float value);
	void CallMoveRL(float value);

	//Debug Function
	void DebugFunction();

	
	UFUNCTION(BlueprintImplementableEvent) void RotateCharacter(ACharacterController* myPlayer);

	void KillPlayer();

	void TryOpenDoor();
	void TryPickUpKey();
	void TryMoveBox();
	
	void PauseGame() { if (m_pCharacterController != nullptr) m_pCharacterController->ShowPauseMenu(); };

	UFUNCTION(BlueprintCallable) void SetPlayerInputFalse() { m_CanPlayerMove = false; }
	UFUNCTION(BlueprintCallable) void SetPlayerInputTrue() { m_CanPlayerMove = true; }
	UFUNCTION(BlueprintCallable) ACharacter* GetCharacterController() { return m_pCharacterController; }

	//CAMERA BULLSHITTERING
	UFUNCTION(BlueprintImplementableEvent) void PlayerCameraHorizontalRotation(float value);
	UFUNCTION(BlueprintImplementableEvent) void PlayerCameraVerticalRotation(float value);
	UFUNCTION(BlueprintImplementableEvent) void PlayerCameraZoom(float value);

	UFUNCTION(BlueprintCallable) void CallPlayerCameraHorizontalRotation(float value, ACPlayerCameraComponent* myPlayer) { if (myPlayer != nullptr) myPlayer->OriginRotateHorizontal(value); }
	UFUNCTION(BlueprintCallable) void CallPlayerCameraVerticalRotation(float value, ACPlayerCameraComponent* myPlayer) { if (myPlayer != nullptr) myPlayer->OriginRotateVertical(value); }
	UFUNCTION(BlueprintCallable) void CallPlayerCameraZoom(float value, ACPlayerCameraComponent* myPlayer) { if (myPlayer != nullptr) myPlayer->ZoomTargetZoom(value); }
	//CAMERA BULLSHITTERING

	
	// returns UseType
	void CallSetIsUsing(int useType) { m_pCharacterController->UFUNCTIONCallSetIsUsing(useType); };
	
	void CallUse();
	
	UPROPERTY()
	TArray<AActor*> m_pCharacterControllerArray;
	UPROPERTY()
	ACharacterController* m_pCharacterController;
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

	UPROPERTY(BlueprintReadWrite, Category = "Script") bool m_CanPlayerMove;
};
