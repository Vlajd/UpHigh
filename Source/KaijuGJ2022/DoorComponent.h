// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterController.h"
#include "DoorComponent.generated.h"

UCLASS()
class KAIJUGJ2022_API ADoorComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent) void CallDoorAnim();
	UPROPERTY(BlueprintReadOnly) bool m_IsOpen;
	UPROPERTY(EditAnywhere, Category = "Script") float m_MinDistanceInCm;

	void OnCallDoorAnim(ACharacterController* characterController);

	UPROPERTY(EditAnywhere, Category = "Script") bool m_NeedsKey;
};
