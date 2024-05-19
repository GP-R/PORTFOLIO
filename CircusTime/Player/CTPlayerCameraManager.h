// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CTPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API ACTPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ACTPlayerCameraManager();

public:
	void AsyncCameraFade(float Time, TFunction<void(void)>&& Callback);

private:
	void ExecuteFadeInCallback();
	void ExecuteFadeOutCallback();

private:
	FTimerHandle CameraFadeInTimerHandle;
	FTimerHandle CameraFadeOutTimerHandle;

	TFunction<void(void)> FadeCallback;
	float Delay = 1.0f;
};
