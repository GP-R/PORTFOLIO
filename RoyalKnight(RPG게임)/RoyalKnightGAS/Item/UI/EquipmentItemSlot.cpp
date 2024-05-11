#include "Item/UI/EquipmentItemSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RKGASPlayerState.h"
#include "Kismet/KismetInputLibrary.h"
#include "Inventory/EquipmentInventory.h"

void UEquipmentItemSlot::Init()
{
	if (EquipmentType == EEquipmentType::Helmet)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("머리")));
	}
	else if (EquipmentType == EEquipmentType::Armor)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("가슴")));
	}
	else if (EquipmentType == EEquipmentType::Pants)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("바지")));
	}
	else if (EquipmentType == EEquipmentType::Shoes)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("신발")));
	}
	else if (EquipmentType == EEquipmentType::Weapon)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("무기")));
	}
	else if (EquipmentType == EEquipmentType::Gloves)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("장갑")));
	}
	else if (EquipmentType == EEquipmentType::Neck)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("목")));
	}
	else if (EquipmentType == EEquipmentType::Ring)
	{
		EquipmentTypeText->SetText(FText::FromString(TEXT("반지")));
	}
}

void UEquipmentItemSlot::SetItem(const FRKItem& Item)
{
	const UEquipmentItem* EquipmentItem = Cast<UEquipmentItem>(Item.GetItemData());
	if (EquipmentItem == nullptr)
	{
		return;
	}

	if (EquipmentItem->GetEquipmentType() != EquipmentType)
	{
		return;
	}

	if (Item.GetItemCount() <= 0)
	{
		EquipmentTypeText->SetVisibility(ESlateVisibility::Visible);
		Clear();
		return;
	}

	ItemType = Item.GetItemData()->GetPrimaryAssetId().PrimaryAssetType;
	SetIcon(Item.GetItemData()->GetIcon());
	bEmptySlot = false;
	EquipmentTypeText->SetVisibility(ESlateVisibility::Hidden);
}

FReply UEquipmentItemSlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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
			PS->GetEquipmentInventory()->OnClikedItemSlotEvent.Broadcast(ItemType, SlotNumber);
			Clear();
			UE_LOG(LogTemp, Log, TEXT("ItemSlotClick"));
		}
	}

	return FReply::Handled();
}

void UEquipmentItemSlot::Clear()
{
	Super::Clear();
	EquipmentTypeText->SetVisibility(ESlateVisibility::Visible);
}