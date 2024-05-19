// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTGameMode.h"
#include "CTPlayerCharacter.h"
#include "CTPlayerController.h"

#include "Kismet/GameplayStatics.h"

ACTGameMode::ACTGameMode()
{
	DefaultPawnClass = ACTPlayerCharacter::StaticClass();
	PlayerControllerClass = ACTPlayerController::StaticClass();
}

void ACTGameMode::BeginPlay()
{
	Super::BeginPlay();

    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
    if (CameraManager)
    {
        CameraManager->StartCameraFade(1.0f, 0.0f, 3.0f, FLinearColor::Black, false, true);
    }
}

APawn* ACTGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
    APawn* SpawnedPawn = Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);

    DefaultPawnInstance = SpawnedPawn;

    return SpawnedPawn;
}
