// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryData.h"
#include "Item/ItemData/ItemData.h"

UInventoryData::UInventoryData()
{

}

void UInventoryData::Init()
{
	Items.Reserve(Size);
    for (int32 i = Items.Num(); i < Size; ++i)
    {
        Items.AddDefaulted();
    }
    Items.SetNum(Size, true);
}

const FRKItem& UInventoryData::GetItem(int32 Index) const
{
	return Items[Index];
}

void UInventoryData::AddItem(const FRKItem& Item, int32 Amount)
{
    bool ItemFound = false;
    for (FRKItem& ItemRef : Items)
    {
        if (ItemRef.GetItemData() == nullptr)
        {
            continue;
        }

        if (ItemRef.GetItemData()->GetPrimaryAssetId() == Item.GetItemData()->GetPrimaryAssetId())
        {
            ItemRef.Add(Amount);
            ItemFound = true;
            break;
        }
    }

    if (!ItemFound)
    {
        for (int i = 0; i < Size; i++)
        {
            if (Items[i].GetItemCount() <= 0)
            {
                Items[i] = std::move(Item);
                return;
            }
        }
    }
}

bool UInventoryData::AddItemToIndex(const FRKItem& Item, int32 Index)
{
    if (Items[Index].GetItemCount() > 0)
    {
        return false;
    }
    Items[Index] = std::move(Item);
    return true;
}

void UInventoryData::RemoveToIndex(int32 Index, int32 Amount)
{
    Items[Index].Remove(Amount);
    if (Items[Index].GetItemCount() <= 0)
    {
        Clear(Index);
    }
}

FRKItem UInventoryData::TakeItem(int32 Index) noexcept
{
    FRKItem Item = std::move(Items[Index]);
    return Item;
}

void UInventoryData::Clear(int32 Index)
{
    Items[Index].Clear();
}

