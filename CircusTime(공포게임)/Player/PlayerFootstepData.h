// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundBase.h"
#include "PlayerFootstepData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CIRCUSTIME_API UPlayerFootstepData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Footstep Data")
	UPhysicalMaterial* GetPhysicalMaterial() const { return PhysicalMaterial; }

	UFUNCTION(BlueprintPure, Category = "Footstep Data")
	TArray<USoundBase*> GetFootstepSounds() const { return Sounds; }

	UFUNCTION(BlueprintPure, Category = "Footstep Data")
	float GetFootstepStride_Walk() const { return WalkStride; }

	UFUNCTION(BlueprintPure, Category = "Footstep Data")
	float GetFootstepStride_Run() const { return RunStride; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	UPhysicalMaterial* PhysicalMaterial;

	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (EditCondition = "bEnableFootsteps"))
	float WalkStride = 160.0f;

	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (EditCondition = "bEnableFootsteps"))
	float RunStride = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	TArray<USoundBase*> Sounds;
};
