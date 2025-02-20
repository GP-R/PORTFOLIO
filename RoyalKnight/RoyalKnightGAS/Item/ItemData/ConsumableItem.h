#pragma once

#include "CoreMinimal.h"
#include "Item/ItemData/ItemData.h"
#include "ConsumableItem.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API UConsumableItem : public UItemData
{
	GENERATED_BODY()
	
public:
	UConsumableItem();

	virtual bool UseItem(AActor* Target) const override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> ItemEffect;
};
