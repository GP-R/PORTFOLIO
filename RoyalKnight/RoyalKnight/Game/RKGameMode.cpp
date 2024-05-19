// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RKGameMode.h"

ARKGameMode::ARKGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/RoyalKnight.RKCharacterPlayer"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/RoyalKnight.RKPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void ARKGameMode::StartPlay()
{
	Super::StartPlay();
}
