#include "Item/Item.h"

FRKItem::FRKItem()
{
	ItemData = nullptr;
	ItemCount = 0;
}

bool FRKItem::Add(int32 Amount)
{
	ItemCount += Amount;

	return true;
}

bool FRKItem::Remove(int32 Amount)
{
	if (ItemCount <= 0)
	{
		return false;
	}
	ItemCount -= Amount;
	return true;
}
