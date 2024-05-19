// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RKAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHT_API URKAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	URKAssetManager();

	static const FPrimaryAssetType	ConsumableItemType;
	static const FPrimaryAssetType	EquipmentItemType;
};
