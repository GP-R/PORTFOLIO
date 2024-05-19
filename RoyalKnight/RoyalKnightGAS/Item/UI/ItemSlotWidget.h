#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/Item.h"
#include "ItemSlotWidget.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetSlotNumber(int32 Num) { SlotNumber = Num; }
	FORCEINLINE int32 GetSlotNumber() { return SlotNumber; }

	FORCEINLINE bool IsSlotEmpty() { return bEmptySlot; }
	virtual void SetItem(const FRKItem& Item);

protected:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	void SetIcon(FSlateBrush Icon);
	void SetAmount(int32 Amount);
	virtual void Clear();

public:
	UPROPERTY(EditAnywhere)
	FSlateBrush ClearBrush;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> AmountText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> IconImage;

	FPrimaryAssetType ItemType;

	UPROPERTY(EditAnywhere)
	int32 SlotNumber;

	bool bEmptySlot = true;
};
