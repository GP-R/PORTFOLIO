#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/ItemData/EquipmentItem.h"
#include "RKGASEquipment.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API ARKGASEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ARKGASEquipment();

	virtual void Equip(AActor* Target, FName SocketName);
	virtual void UnEquip();

	EEquipmentType GetEquipmentType() { return EquipmentType; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> EquipmentMesh;

	UPROPERTY(EditAnywhere, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> EquipmentEffect;

	UPROPERTY(EditAnywhere, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
	EEquipmentType EquipmentType;
};
