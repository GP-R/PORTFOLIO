// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemData/ItemData.h"
#include "Item.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct ROYALKNIGHTGAS_API FRKItem
{
	GENERATED_BODY()

public:
	FRKItem();

    FRKItem& operator=(const FRKItem& Other) {
        if (this != &Other) {
            ItemData = Other.ItemData;
            ItemCount = Other.ItemCount;
        }
        return *this;
    }

    FRKItem(FRKItem&& Other) noexcept
        : ItemData(Other.ItemData), ItemCount(Other.ItemCount) 
    {
        Other.ItemData = nullptr;
        Other.ItemCount = 0;
    }

    FRKItem& operator=(FRKItem&& Other) noexcept 
    {
        if (this != &Other) {
            ItemData = Other.ItemData;
            ItemCount = Other.ItemCount;
            Other.ItemData = nullptr;
            Other.ItemCount = 0;
        }
        return *this;
    }
	bool Add(int32 Amount);
	bool Remove(int32 Amount);
    void Clear() 
    { 
        ItemData = nullptr;
        ItemCount = 0;
    }

    const UItemData* GetItemData() const { return ItemData; }
    int32 GetItemCount() const { return ItemCount; }


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 ItemCount;

};
