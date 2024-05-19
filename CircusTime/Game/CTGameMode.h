// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API ACTGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACTGameMode();

	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(Transient)
	APawn* DefaultPawnInstance;
};
