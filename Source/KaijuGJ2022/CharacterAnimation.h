// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class KAIJUGJ2022_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable) void SetIsMoving(bool isMoving) { m_CharacterIsMoving = isMoving; }
	
	UFUNCTION(BlueprintCallable) bool IsMoving() { return m_CharacterIsMoving; }

	bool m_CharacterIsMoving;
};
