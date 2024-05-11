#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "RKTA_Trace.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API ARKTA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	ARKTA_Trace();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;
	void SetShowDebug(bool InShowDebug) { bShowDebug = InShowDebug; }

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	float AttackRange;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	bool bShowDebug = false;
};
