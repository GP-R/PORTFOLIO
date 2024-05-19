#include "Inventory/EquipmentInventory.h"
#include "Inventory/InventoryData.h"
#include "Inventory/PlayerInventory.h"
#include "Player/RKGASPlayerState.h"

void UEquipmentInventory::Init()
{
	EquippedItems->Init();

	FScriptDelegate BindUseItemFunc;
	BindUseItemFunc.BindUFunction(this, "UnEquip");
	OnClikedItemSlotEvent.AddUnique(BindUseItemFunc);
}

void UEquipmentInventory::AddItem(const FRKItem& Item, int32 Amount)
{
	const UEquipmentItem* ItemData = Cast<UEquipmentItem>(Item.GetItemData());
	if (ItemData != nullptr)
	{
		FRKItem DuplicatedItem = GetDuplicatedEquipmentTypeItem(ItemData->GetEquipmentType());
		if (DuplicatedItem.GetItemCount() > 0)
		{
			ARKGASPlayerState* PS = Cast<ARKGASPlayerState>(GetOwner());
			TransferItem(PS->GetPlayerInventory(), DuplicatedItem);
		}

		if (ItemData->GetEquipmentType() == EEquipmentType::Helmet)
		{
			EquippedItems->AddItemToIndex(Item, 1);
		}
		else if (ItemData->GetEquipmentType() == EEquipmentType::Armor)
		{
			EquippedItems->AddItemToIndex(Item, 2);
		}
		else if (ItemData->GetEquipmentType() == EEquipmentType::Pants)
		{
			EquippedItems->AddItemToIndex(Item, 3);
		}
		else if (ItemData->GetEquipmentType() == EEquipmentType::Shoes)
		{
			EquippedItems->AddItemToIndex(Item, 4);
		}
		else if (ItemData->GetEquipmentType() == EEquipmentType::Weapon)
		{
			EquippedItems->AddItemToIndex(Item, 5);
		}
		else if (ItemData->GetEquipmentType() == EEquipmentType::Gloves)
		{
			EquippedItems->AddItemToIndex(Item, 6);
		}
		else if (ItemData->GetEquipmentType() == EEquipmentType::Neck)
		{
			EquippedItems->AddItemToIndex(Item, 7);
		}
		else if (ItemData->GetEquipmentType() == EEquipmentType::Ring)
		{
			EquippedItems->AddItemToIndex(Item, 8);
		}

		ItemData->UseItem(GetOwner());
		//EquippedItems->AddItem(Item, Amount);
		UpdateInventoryEvent.Broadcast();
	}
}

void UEquipmentInventory::UnEquip(FPrimaryAssetType ItemType, int32 SlotNumber)
{
	const UEquipmentItem* ItemData = Cast<UEquipmentItem>(EquippedItems->GetItem(SlotNumber).GetItemData());
	if (ItemData != nullptr)
	{
		ItemData->DisUse(GetOwner());
		ARKGASPlayerState* PS = Cast<ARKGASPlayerState>(GetOwner());
		TransferItem(PS->GetPlayerInventory(), EquippedItems->TakeItem(SlotNumber));
	}
}

FRKItem UEquipmentInventory::GetDuplicatedEquipmentTypeItem(EEquipmentType EquipmentType)
{
	for (int i = 0; i < EquippedItems->GetSize(); i++)
	{
		const UEquipmentItem* ItemData = Cast<UEquipmentItem>(EquippedItems->GetItem(i).GetItemData());
		if (ItemData != nullptr)
		{
			if (ItemData->GetEquipmentType() == EquipmentType)
			{
				return EquippedItems->TakeItem(i);
			}
		}
	}
	return FRKItem();
}

