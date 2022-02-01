// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleGamemode.h"

ASampleGamemode::ASampleGamemode() {

	//DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = ASamplePlayerController::StaticClass();
}
