#include "Item/ItemData/EquipmentItem.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Tag/RKGameplayTag.h"
#include "Equipment/RKGASWeaponActor.h"

UEquipmentItem::UEquipmentItem()
	:UItemData()
{
	Type = URKAssetManager::EquipmentItemType;
}

bool UEquipmentItem::UseItem(AActor* Target) const
{
	Super::UseItem(Target);

	FGameplayEventData EventData;
	if (EquipmentClass)
	{
		EventData.OptionalObject = EquipmentClass;
		DisUse(Target);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Target, RKTAG_EVENT_CHARACTER_WEAPONEQUIP, EventData);
		return true;
	}
	return false;
}

void UEquipmentItem::DisUse(AActor* Target) const
{
	FGameplayEventData EventData;
	if (EquipmentClass)
	{
		EventData.OptionalObject = EquipmentClass;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Target, RKTAG_EVENT_CHARACTER_WEAPONUNEQUIP, EventData);
	}
}
