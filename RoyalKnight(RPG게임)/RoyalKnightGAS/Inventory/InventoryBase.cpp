#include "Inventory/InventoryBase.h"
#include "Inventory/InventoryData.h"

UInventoryBase::UInventoryBase()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryBase::AddItem(const FRKItem& Item, int32 Amount)
{
}

void UInventoryBase::LoadDefaultItems()
{
}

void UInventoryBase::TransferItem(UInventoryBase* ToInventory, const FRKItem& Item)
{
	ToInventory->AddItem(Item, 1);
}

void UInventoryBase::BeginPlay()
{
	Super::BeginPlay();

}

void UInventoryBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

