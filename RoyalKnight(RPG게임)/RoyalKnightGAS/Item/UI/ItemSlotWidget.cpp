#include "Item/UI/ItemSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/KismetInputLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RKGASPlayerState.h"
#include "Inventory/InventoryBase.h"
#include "Inventory/PlayerInventory.h"

void UItemSlotWidget::SetItem(const FRKItem& Item)
{
	if (Item.GetItemCount() <= 0)
	{
		Clear();
		return;
	}

	ItemType = Item.GetItemData()->GetPrimaryAssetId().PrimaryAssetType;
	SetIcon(Item.GetItemData()->GetIcon());
	SetAmount(Item.GetItemCount());
	bEmptySlot = false;
}

FReply UItemSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bEmptySlot)
	{
		return FReply::Handled();
	}

	if (UKismetInputLibrary::PointerEvent_IsMouseButtonDown(InMouseEvent, EKeys::RightMouseButton))
	{
		ARKGASPlayerState* PS = Cast<ARKGASPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
		if (PS != nullptr)
		{
			PS->GetPlayerInventory()->OnClikedItemSlotEvent.Broadcast(ItemType, SlotNumber);
			UE_LOG(LogTemp, Log, TEXT("ItemSlotClick"));
		}
	}
	else if(UKismetInputLibrary::PointerEvent_IsMouseButtonDown(InMouseEvent, EKeys::LeftMouseButton))
	{
		FReply Event = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		if (Event.IsEventHandled())
		{
			UE_LOG(LogTemp, Log, TEXT("ItemSlotDrag"));
		}
		return Event;
	}
	
	return FReply::Handled();
}

void UItemSlotWidget::SetIcon(FSlateBrush Icon)
{
	IconImage->SetBrush(Icon);
}

void UItemSlotWidget::SetAmount(int32 Amount)
{
	if (Amount <= 0)
	{
		AmountText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	AmountText->SetText(FText::FromString(FString::FromInt(Amount)));
	AmountText->SetVisibility(ESlateVisibility::Visible);
}

void UItemSlotWidget::Clear()
{
	SetIcon(ClearBrush);
	SetAmount(0);
	bEmptySlot = true;
}
