#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/Item.h"
#include "InventoryGridWidget.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();

	void CreateItemSlots(int32 Size, int32 SlotsPerRow);

	void UpdateSlot(const FRKItem& ItemData, int32 SlotNumber);

	int32 GetGridSize() { return ItemSlots.Num(); }

private:
	

protected:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* InventoryGrid;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemSlotWidget> ItemSlotClass;

	TArray<class UItemSlotWidget*> ItemSlots;
};
