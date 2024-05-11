// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryBase.h"
#include "Item/ItemData/EquipmentItem.h"
#include "EquipmentInventory.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API UEquipmentInventory : public UInventoryBase
{
	GENERATED_BODY()
	
public:
	void Init();

	virtual void AddItem(const FRKItem& Item, int32 Amount) override;

	class UInventoryData* GetEquippedItems() { return EquippedItems; }

protected:
	UFUNCTION()
	void UnEquip(FPrimaryAssetType ItemType, int32 SlotNumber);

	FRKItem GetDuplicatedEquipmentTypeItem(EEquipmentType EquipmentType);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	class UInventoryData* EquippedItems;
};
