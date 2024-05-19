#pragma once

#include "CoreMinimal.h"
#include "Item/ItemData/ItemData.h"
#include "EquipmentItem.generated.h"

UENUM()
enum class EEquipmentType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Helmet UMETA(DisplayName = "Helmet"),
	Armor UMETA(DisplayName = "Armor"),
	Pants UMETA(DisplayName = "Pants"),
	Shoes UMETA(DisplayName = "Shoes"),
	Weapon UMETA(DisplayName = "Weapon"),
	Gloves UMETA(DisplayName = "Gloves"),
	Neck UMETA(DisplayName = "Neck"),
	Ring UMETA(DisplayName = "Ring"),
};

UCLASS()
class ROYALKNIGHTGAS_API UEquipmentItem : public UItemData
{
	GENERATED_BODY()

public:
	UEquipmentItem();

	EEquipmentType GetEquipmentType() const { return EquipmentType; }

	virtual bool UseItem(AActor* Target) const override;

	void DisUse(AActor* Target) const;

protected:

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSubclassOf<class ARKGASEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = Equipment)
	EEquipmentType EquipmentType;
};
