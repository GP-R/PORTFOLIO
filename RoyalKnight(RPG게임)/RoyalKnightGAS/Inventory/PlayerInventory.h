#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryBase.h"
#include "Item/Item.h"
#include "PlayerInventory.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API UPlayerInventory : public UInventoryBase
{
	GENERATED_BODY()

public:
	void Init();

	virtual void AddItem(const FRKItem& Item, int32 Amount) override;

	virtual void LoadDefaultItems() override;
	class UInventoryData* GetEquipmentItems() { return EquipmentItems; }
	class UInventoryData* GetConsumableItems() { return ConsumableItems; }
	class UInventoryData* GetETCItems() { return ETCItems; }

protected:
	UFUNCTION()
	void UseItem(FPrimaryAssetType ItemType, int32 SlotNumber);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	class UInventoryData* EquipmentItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	class UInventoryData* ConsumableItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	class UInventoryData* ETCItems;
};

