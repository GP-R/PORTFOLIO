#include "Animation/RKAN_AttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GA/TargetActor/RKTA_Trace.h"

URKAN_AttackHitCheck::URKAN_AttackHitCheck()
{

	ComboAttackLevel = 1.0f;
}

FString URKAN_AttackHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("GASAttackHitCheck");
}

void URKAN_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			FGameplayEventData PayloadData;
			PayloadData.EventMagnitude = ComboAttackLevel;
			if (TargetActorClass)
			{
				PayloadData.OptionalObject = TargetActorClass;
			}
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
		}
	}
}
