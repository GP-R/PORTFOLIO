#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "RKAN_AttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API URKAN_AttackHitCheck : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	URKAN_AttackHitCheck();

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag TriggerGameplayTag;

	UPROPERTY(EditAnywhere)
	float ComboAttackLevel;

	UPROPERTY(EditAnywhere, Category = "GAS", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ARKTA_Trace> TargetActorClass;
};
