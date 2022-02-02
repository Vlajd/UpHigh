// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTriggerDeathArea.h"

AEnemyTriggerDeathArea::AEnemyTriggerDeathArea() {
	
	OnActorBeginOverlap.AddDynamic(this, &AEnemyTriggerDeathArea::Event);
}

void AEnemyTriggerDeathArea::BeginPlay() {

	Super::BeginPlay();
	m_pPlayerController = Cast<ASamplePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AEnemyTriggerDeathArea::Event(class AActor* overlappedActor, class AActor* otherActor) {

	if (otherActor && otherActor != this) {

		if (m_pPlayerController != nullptr) {

			// EXECUTE DEATH
			m_pPlayerController->KillPlayer();
		}
		else
			GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Red, TEXT("EVENT::NoPlayerControllerFound!"));

	}
}
