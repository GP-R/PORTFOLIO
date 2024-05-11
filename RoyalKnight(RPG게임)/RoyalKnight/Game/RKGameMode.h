// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RKGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHT_API ARKGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARKGameMode();

	virtual void StartPlay() override;
};
