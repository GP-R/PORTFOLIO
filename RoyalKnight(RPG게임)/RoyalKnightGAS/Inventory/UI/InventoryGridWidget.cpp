#include "Inventory/UI/InventoryGridWidget.h"
#include "Components/UniformGridPanel.h"
#include "Item/UI/ItemSlotWidget.h"

void UInventoryGridWidget::Init()
{
	
}

void UInventoryGridWidget::CreateItemSlots(int32 Size, int32 SlotsPerRow)
{
	if (SlotsPerRow == 0)
	{
		return;
	}

	ItemSlots.Reserve(Size);
	for (int i = 0; i < Size; i++)
	{
		UItemSlotWidget* ItemSlot = CreateWidget<UItemSlotWidget>(InventoryGrid, ItemSlotClass);
		if (ItemSlot != nullptr)
		{
			ItemSlot->SetSlotNumber(i);
			int32 Row = i / SlotsPerRow;
			int32 Column = i % SlotsPerRow;

			InventoryGrid->AddChildToUniformGrid(ItemSlot, Row, Column);
			ItemSlots.Add(ItemSlot);
		}
	}
}

void UInventoryGridWidget::UpdateSlot(const FRKItem& ItemData, int32 SlotNumber)
{
	for (auto ItemSlot : ItemSlots)
	{
		if(ItemSlot->GetSlotNumber() == SlotNumber)
		{
			ItemSlot->SetItem(ItemData);
		}
	}
}
