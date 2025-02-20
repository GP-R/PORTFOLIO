#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventoryWidget.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init();

	void CreateItemSlots(int32 Size, int32 SlotPerRow);

	void SetEquipmentItemData(class UInventoryData* InventoryData);
	void SetConsumableItemData(class UInventoryData* InventoryData);
	void SetETCItemData(class UInventoryData* InventoryData);

private:
	UFUNCTION()
	void UpdateInventory();

	UFUNCTION()
	void OnClickEquipmentButton();

	UFUNCTION()
	void OnClickConsumableButton();

	UFUNCTION()
	void OnClickETCButton();

protected:
	UPROPERTY(meta = (BindWidget))
	class UInventoryGridWidget* EquipmentInventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UInventoryGridWidget* ConsumableInventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UInventoryGridWidget* ETCInventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConsumableButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ETCButton;

private:
	class UInventoryData* EquipmentItems;
	class UInventoryData* ConsumableItems;
	class UInventoryData* ETCItems;
};
