#include "Inventory/UI/EquipmentInventoryWidget.h"
#include "Item/UI/EquipmentItemSlot.h"
#include "Inventory/InventoryData.h"
#include "Components/TextBlock.h"

#include "Player/RKGASPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/EquipmentInventory.h"
#include "Player/RKGASPlayerState.h"

void UEquipmentInventoryWidget::Init()
{
	EquipmentSlots.Add(HelmetSlot);
	EquipmentSlots.Add(ArmorSlot);
	EquipmentSlots.Add(PantsSlot);
	EquipmentSlots.Add(ShoesSlot);
	EquipmentSlots.Add(WeaponSlot);
	EquipmentSlots.Add(GlovesSlot);
	EquipmentSlots.Add(NeckSlot);
	EquipmentSlots.Add(RingSlot);

	for (TObjectPtr<UEquipmentItemSlot>& EquipmentSlot : EquipmentSlots)
	{
		EquipmentSlot->Init();
	}

	FScriptDelegate UpdateInventoryEvent;
	UpdateInventoryEvent.BindUFunction(this, "UpdateInventory");
	ARKGASPlayerState* PS = Cast<ARKGASPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (PS)
	{
		PS->GetEquipmentInventory()->UpdateInventoryEvent.AddUnique(UpdateInventoryEvent);
		SetAttackRateText(PS->GetAttackRate());
		SetMaxHealthText(PS->GetMaxHealth());
		SetMaxManaText(PS->GetMaxMana());
	}


}

void UEquipmentInventoryWidget::SetEquippedItemData(UInventoryData* InventoryData)
{
	EquippedItems = InventoryData;
}

void UEquipmentInventoryWidget::SetAttackRateText(float Value)
{
	int IntValue = FMath::RoundToInt(Value);
	FString FormattedString = FString::Printf(TEXT("공격력 : %d"), IntValue);
	AttackRateText->SetText(FText::FromString(FormattedString));
}

void UEquipmentInventoryWidget::SetMaxHealthText(float Value)
{
	int IntValue = FMath::RoundToInt(Value);
	FString FormattedString = FString::Printf(TEXT("최대 체력 : %d"), IntValue);
	MaxHealthText->SetText(FText::FromString(FormattedString));
}

void UEquipmentInventoryWidget::SetMaxManaText(float Value)
{
	int IntValue = FMath::RoundToInt(Value);
	FString FormattedString = FString::Printf(TEXT("최대 마나 : %d"), IntValue);
	MaxManaText->SetText(FText::FromString(FormattedString));
}


void UEquipmentInventoryWidget::UpdateInventory()
{
	for (int i = 0; i < EquippedItems->GetSize(); i++)
	{
		for (TObjectPtr<UEquipmentItemSlot>& EquipmentSlot : EquipmentSlots)
		{
			EquipmentSlot->SetItem(EquippedItems->GetItem(i));
		}
	}
}
