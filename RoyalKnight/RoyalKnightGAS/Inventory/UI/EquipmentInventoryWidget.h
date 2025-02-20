#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentInventoryWidget.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API UEquipmentInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init();

	void SetEquippedItemData(class UInventoryData* InventoryData);

	UFUNCTION()
	void SetAttackRateText(float Value);

	UFUNCTION()
	void SetMaxHealthText(float Value);

	UFUNCTION()
	void SetMaxManaText(float Value);

private:
	UFUNCTION()
	void UpdateInventory();

	
private:
	UPROPERTY()
	TArray<TObjectPtr<class UEquipmentItemSlot>> EquipmentSlots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> HelmetSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> ArmorSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> PantsSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> ShoesSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> WeaponSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> GlovesSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> NeckSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEquipmentItemSlot> RingSlot;

	class UInventoryData* EquippedItems;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> AttackRateText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxHealthText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxManaText;

};
