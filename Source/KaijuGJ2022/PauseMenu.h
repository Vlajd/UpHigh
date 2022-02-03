// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class KAIJUGJ2022_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent) void ShowWidget();
	UFUNCTION(BlueprintImplementableEvent) void ResumeGame();
};
