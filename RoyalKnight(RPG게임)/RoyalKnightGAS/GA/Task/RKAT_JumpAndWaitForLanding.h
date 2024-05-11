// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "RKAT_JumpAndWaitForLanding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJumpAndWaitForLandingDelegate);
/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API URKAT_JumpAndWaitForLanding : public UAbilityTask
{
	GENERATED_BODY()

public:
	URKAT_JumpAndWaitForLanding();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "JumpAndWaitForLanding", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static URKAT_JumpAndWaitForLanding* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY(BlueprintAssignable)
	FJumpAndWaitForLandingDelegate OnComplete;

protected:
	UFUNCTION()
	void OnLandedCallback(const FHitResult& Hit);
};
