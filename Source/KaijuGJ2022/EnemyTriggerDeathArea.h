// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "SamplePlayerController.h"
#include "EnemyTriggerDeathArea.generated.h"

/**
 * 
 */
UCLASS() class KAIJUGJ2022_API AEnemyTriggerDeathArea : public ATriggerBox {
	
	GENERATED_BODY()

	public:
		AEnemyTriggerDeathArea();

	protected:

		virtual void BeginPlay() override;
		
	public:
	
		UFUNCTION() void Event(class AActor* overlappedActor, class AActor* otherActor);

		ASamplePlayerController* m_pPlayerController;
};
