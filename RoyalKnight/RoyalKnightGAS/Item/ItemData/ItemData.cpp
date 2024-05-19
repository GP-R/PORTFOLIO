#include "Item/ItemData/ItemData.h"

UItemData::UItemData()
{
}

FPrimaryAssetId UItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(Type, GetFName());
}

bool UItemData::UseItem(AActor* Target) const
{
	return true;
}
