#pragma once

#include "CoreMinimal.h"
#include "Item/UI/ItemSlotWidget.h"
#include "Item/ItemData/EquipmentItem.h"
#include "EquipmentItemSlot.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API UEquipmentItemSlot : public UItemSlotWidget
{
	GENERATED_BODY()
	
public:
	void Init();
	virtual void SetItem(const FRKItem& Item) override;
	virtual void Clear() override;

protected:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> EquipmentTypeText;

	UPROPERTY(EditAnywhere)
	EEquipmentType EquipmentType;
};
