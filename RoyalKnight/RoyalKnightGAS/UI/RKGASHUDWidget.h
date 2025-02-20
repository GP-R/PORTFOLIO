#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RKGASHUDWidget.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API URKGASHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthPercentage(float HealthPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxMana(float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMana(float CurrentMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPercentage(float ManaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateSkillIcon(FSlateBrush Icon, int32 SkillIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ClearSkillIcon();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlaySkillCooldownAnimation(float Duration, int32 SkillIndex);
};
