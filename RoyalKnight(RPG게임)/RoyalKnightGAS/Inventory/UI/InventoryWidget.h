// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void CreateItemSlots(int32 Size, int32 SlotPerRow);

	void UpdateInventory(class UInventoryData* InventoryData);

protected:
	UPROPERTY(meta = (BindWidget))
	class UInventoryGridWidget* InventoryGrid;
};
