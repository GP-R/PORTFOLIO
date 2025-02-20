#pragma once

#include "CoreMinimal.h"
#include "Character/RKCharacterPlayer.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "RKGASCharacterPlayer.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API ARKGASCharacterPlayer : public ARKCharacterPlayer, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ARKGASCharacterPlayer();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void SetupGASInputComponent();
	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);

	UFUNCTION()
	virtual void OnOutOfHealth();

	void Equip(const FGameplayEventData* EventData);
	void Unequip(const FGameplayEventData* EventData);

private:
	void ToggleInventory();
	void ToggleEquipmentInventory();

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayEffect> InitStatEffect;

	UPROPERTY()
	TArray<class ARKGASEquipment*> EquippedItems;

protected:
	UPROPERTY(EditAnywhere)
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere)
	FName HelmetSocketName;

	UPROPERTY(EditAnywhere)
	FName ArmorSocketName;

	UPROPERTY(EditAnywhere)
	FName PantsSocketName;

	UPROPERTY(EditAnywhere)
	FName ShoesSocketName;

	UPROPERTY(EditAnywhere)
	FName GlovesSocketName;

	UPROPERTY(EditAnywhere)
	FName NeckSocketName;

	UPROPERTY(EditAnywhere)
	FName RingSocketName;
};
