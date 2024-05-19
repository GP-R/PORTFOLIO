// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundCue.h"
#include "DialogueData.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_BODY()

public:
	FDialogueData() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	USoundCue* Sound;
};