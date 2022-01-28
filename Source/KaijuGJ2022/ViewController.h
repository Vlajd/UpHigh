// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewController.generated.h"

UCLASS()
class KAIJUGJ2022_API AViewController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViewController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		AActor* ViewActor;

};
