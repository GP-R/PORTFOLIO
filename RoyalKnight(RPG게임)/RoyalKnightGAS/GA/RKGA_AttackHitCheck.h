// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RKGA_AttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API URKGA_AttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	URKGA_AttackHitCheck();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UGameplayEffect> AttackBuffEffect;

	float CurrentLevel;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class ARKTA_Trace> TargetActorClass;
};
