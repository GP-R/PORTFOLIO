#include "Inventory/UI/InventoryWidget.h"
#include "Inventory/UI/InventoryGridWidget.h"
#include "Inventory/InventoryData.h"

void UInventoryWidget::CreateItemSlots(int32 Size, int32 SlotPerRow)
{
	//InventoryGrid->CreateItemSlots(Size, SlotPerRow);
}

void UInventoryWidget::UpdateInventory(UInventoryData* InventoryData)
{
	/*int32 SlotNumber = 0;
	for (auto& Item : InventoryData->GetItems())
	{
		InventoryGrid->UpdateSlot(Item, SlotNumber);
		SlotNumber++;
	}*/
}
