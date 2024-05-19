#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/PrimaryAssetId.h"
#include "Item/Item.h"
#include "InventoryBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateInventoryDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClickedItemSlotDelegate, FPrimaryAssetType, Type, int32, SlotNumber);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROYALKNIGHTGAS_API UInventoryBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryBase();

	virtual void AddItem(const FRKItem& Item, int32 Amount);

	virtual void LoadDefaultItems();
	virtual void TransferItem(UInventoryBase* ToInventory, const FRKItem& Item);

	FUpdateInventoryDelegate UpdateInventoryEvent;
	FOnClickedItemSlotDelegate OnClikedItemSlotEvent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
