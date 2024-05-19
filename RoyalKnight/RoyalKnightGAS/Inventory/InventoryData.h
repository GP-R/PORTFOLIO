// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item/Item.h"
#include "InventoryData.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API UInventoryData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UInventoryData();

	void Init();

	const FRKItem& GetItem(int32 Index) const;
	FORCEINLINE int32 GetSize() { return Size; }

	void AddItem(const FRKItem& Item, int32 Amount);
	bool AddItemToIndex(const FRKItem& Item, int32 Index);
	void RemoveToIndex(int32 Index, int32 Amount);

	FRKItem TakeItem(int32 Index) noexcept;
private:
	void Clear(int32 Index);

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	TArray<FRKItem> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 Size;

};
