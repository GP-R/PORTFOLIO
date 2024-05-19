#include "Inventory/PlayerInventory.h"
#include "Inventory/InventoryData.h"
#include "Game/RKAssetManager.h"
#include "Player/\RKGASPlayerState.h"
#include "Inventory/EquipmentInventory.h"

void UPlayerInventory::Init()
{
	EquipmentItems->Init();
	ConsumableItems->Init();
	ETCItems->Init();

	FScriptDelegate BindUseItemFunc;
	BindUseItemFunc.BindUFunction(this, "UseItem");
	OnClikedItemSlotEvent.AddUnique(BindUseItemFunc);
}

void UPlayerInventory::AddItem(const FRKItem& Item, int32 Amount)
{
	if (Item.GetItemData()->GetPrimaryAssetId().PrimaryAssetType == URKAssetManager::EquipmentItemType)
	{
		EquipmentItems->AddItem(Item, Amount);
	}
	else if (Item.GetItemData()->GetPrimaryAssetId().PrimaryAssetType == URKAssetManager::ConsumableItemType)
	{
		ConsumableItems->AddItem(Item, Amount);
	}
	else
	{
		ETCItems->AddItem(Item, Amount);
	}
}

void UPlayerInventory::UseItem(FPrimaryAssetType ItemType, int32 SlotNumber)
{
	if (ItemType == URKAssetManager::EquipmentItemType)
	{
		ARKGASPlayerState* PS = Cast<ARKGASPlayerState>(GetOwner());

		TransferItem(PS->GetEquipmentInventory(), EquipmentItems->TakeItem(SlotNumber));
		
		UpdateInventoryEvent.Broadcast();
	}
	else if (ItemType == URKAssetManager::ConsumableItemType)
	{
		ConsumableItems->GetItem(SlotNumber).GetItemData()->UseItem(GetOwner());
		ConsumableItems->RemoveToIndex(SlotNumber, 1);
		UpdateInventoryEvent.Broadcast();
	}
}

void UPlayerInventory::LoadDefaultItems()
{

	UpdateInventoryEvent.Broadcast();
}
