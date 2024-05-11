#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Game/RKAssetManager.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class ROYALKNIGHTGAS_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UItemData();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	FORCEINLINE FText GetItemName() const { return Name; }
	FORCEINLINE FText GetDescription() const { return Description; }
	FORCEINLINE FSlateBrush GetIcon() const { return Icon; }
	FORCEINLINE int32 GetMaxStack() const { return MaxStack; }

	virtual bool UseItem(AActor* Target) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxStack;
};
