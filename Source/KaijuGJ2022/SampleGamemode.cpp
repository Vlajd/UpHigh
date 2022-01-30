// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleGamemode.h"

ASampleGamemode::ASampleGamemode() {

	DefaultPawnClass = ACharacterController::StaticClass();
	PlayerControllerClass = ASamplePlayerController::StaticClass();
}
