#include "Item/ItemData/ConsumableItem.h"
#include "Player/RKGASPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UConsumableItem::UConsumableItem()
	:UItemData()
{
	Type = URKAssetManager::ConsumableItemType;
}

bool UConsumableItem::UseItem(AActor* Target) const
{
	Super::UseItem(Target);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC)
	{
		FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(ItemEffect, 1, EffectContext);
		if (EffectSpecHandle.IsValid())
		{
			TargetASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
			return true;
			UE_LOG(LogTemp, Log, TEXT("Consume"));
		}
	}
	return false;
}
