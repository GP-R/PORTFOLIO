#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "RKGC_AttackHit.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API URKGC_AttackHit : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	URKGC_AttackHit();

	virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayCue)
	TObjectPtr<class UParticleSystem> ParticleSystem;

};
