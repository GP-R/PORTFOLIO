#include "Inventory/UI/PlayerInventoryWidget.h"
#include "Inventory/UI/InventoryGridWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "Player/RKGASPlayerState.h"
#include "Inventory/InventoryData.h"
#include "Inventory/PlayerInventory.h"

void UPlayerInventoryWidget::Init()
{
	OnClickEquipmentButton();

	FScriptDelegate EquipmentButtonEvent;
	EquipmentButtonEvent.BindUFunction(this, "OnClickEquipmentButton");
	EquipmentButton->OnClicked.Add(EquipmentButtonEvent);

	FScriptDelegate ConsumableButtonEvent;
	ConsumableButtonEvent.BindUFunction(this, "OnClickConsumableButton");
	ConsumableButton->OnClicked.Add(ConsumableButtonEvent);

	FScriptDelegate ETCButtonEvent;
	ETCButtonEvent.BindUFunction(this, "OnClickETCButton");
	ETCButton->OnClicked.Add(ETCButtonEvent);

	FScriptDelegate UpdateInventoryEvent;
	UpdateInventoryEvent.BindUFunction(this, "UpdateInventory");
	ARKGASPlayerState* PS = Cast<ARKGASPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (PS)
	{
		PS->GetPlayerInventory()->UpdateInventoryEvent.AddUnique(UpdateInventoryEvent);
	}
}

void UPlayerInventoryWidget::CreateItemSlots(int32 Size, int32 SlotPerRow)
{
	EquipmentInventoryGrid->CreateItemSlots(Size, SlotPerRow);
	ConsumableInventoryGrid->CreateItemSlots(Size, SlotPerRow);
	ETCInventoryGrid->CreateItemSlots(Size, SlotPerRow);
}

void UPlayerInventoryWidget::UpdateInventory()
{
	for (int i = 0; i < EquipmentItems->GetSize(); i++)
	{
		EquipmentInventoryGrid->UpdateSlot(EquipmentItems->GetItem(i), i);
	}
	
	for (int i = 0; i < ConsumableItems->GetSize(); i++)
	{
		ConsumableInventoryGrid->UpdateSlot(ConsumableItems->GetItem(i), i);
	}

	for (int i = 0; i < ETCItems->GetSize(); i++)
	{
		ETCInventoryGrid->UpdateSlot(ETCItems->GetItem(i), i);
	}
}

void UPlayerInventoryWidget::OnClickEquipmentButton()
{
	EquipmentInventoryGrid->SetVisibility(ESlateVisibility::Visible);
	ConsumableInventoryGrid->SetVisibility(ESlateVisibility::Hidden);
	ETCInventoryGrid->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInventoryWidget::OnClickConsumableButton()
{
	EquipmentInventoryGrid->SetVisibility(ESlateVisibility::Hidden);
	ConsumableInventoryGrid->SetVisibility(ESlateVisibility::Visible);
	ETCInventoryGrid->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInventoryWidget::OnClickETCButton()
{
	EquipmentInventoryGrid->SetVisibility(ESlateVisibility::Hidden);
	ConsumableInventoryGrid->SetVisibility(ESlateVisibility::Hidden);
	ETCInventoryGrid->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerInventoryWidget::SetEquipmentItemData(UInventoryData* InventoryData)
{
	EquipmentItems = InventoryData;
}

void UPlayerInventoryWidget::SetConsumableItemData(UInventoryData* InventoryData)
{
	ConsumableItems = InventoryData;
}

void UPlayerInventoryWidget::SetETCItemData(UInventoryData* InventoryData)
{
	ETCItems = InventoryData;
}

