// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RKGA_SkillBase.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API URKGA_SkillBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	URKGA_SkillBase();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	FORCEINLINE int32 GetInputID() { return InputID; }
	FORCEINLINE FSlateBrush GetSkillIcon() { return SkillIcon; }

protected:
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> ActiveSkillActionMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> BuffEffect;

private:
	UPROPERTY(EditAnywhere)
	int32 InputID;

	UPROPERTY(EditAnywhere)
	FSlateBrush SkillIcon;
};
