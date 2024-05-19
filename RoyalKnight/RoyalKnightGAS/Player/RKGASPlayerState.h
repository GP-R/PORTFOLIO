// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "RKGASPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API ARKGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ARKGASPlayerState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class URKCharacterAttributeSet* GetAttributeSetBase() const;

	class UPlayerInventory* GetPlayerInventory() { return PlayerInventory; }
	class UEquipmentInventory* GetEquipmentInventory() { return EquipmentInventory; }

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMana() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable)
	float GetAttackRate() const;
protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class URKCharacterAttributeSet> AttributeSet;

protected:
	UPROPERTY(EditAnywhere, Category = Inventory)
	TObjectPtr<class UPlayerInventory> PlayerInventory;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TObjectPtr<class UEquipmentInventory> EquipmentInventory;

protected:
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle ManaChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void AttackRateChanged(const FOnAttributeChangeData& Data);
};
