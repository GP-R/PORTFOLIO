#include "GA/RKGA_SkillBase.h"
#include "Character/RKGASCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Player/RKGASPlayerController.h"
#include "UI/RKGASHUDWidget.h"

URKGA_SkillBase::URKGA_SkillBase()
	:InputID(0)
{
}

void URKGA_SkillBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!ActiveSkillActionMontage)
	{
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("%f"), GetCooldownTimeRemaining());
	ARKGASCharacterPlayer* TargetCharacter = Cast<ARKGASCharacterPlayer>(ActorInfo->AvatarActor.Get());
	if (!TargetCharacter)
	{
		return;
	}
	ARKGASPlayerController* PC = Cast<ARKGASPlayerController>(TargetCharacter->GetController());
	if (PC)
	{
		PC->GetHUD()->PlaySkillCooldownAnimation(GetCooldownTimeRemaining(), InputID);
	}
	if (BuffEffect)
	{
		FGameplayEffectSpecHandle BuffEffectSpecHandle = MakeOutgoingGameplayEffectSpec(BuffEffect);
		if (BuffEffectSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, BuffEffectSpecHandle);
		}
	}

	TargetCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("SkillMontage"), ActiveSkillActionMontage, 1.0f);
	PlayMontageTask->OnCompleted.AddDynamic(this, &URKGA_SkillBase::OnCompleteCallback);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &URKGA_SkillBase::OnInterruptedCallback);

	PlayMontageTask->ReadyForActivation();
}

void URKGA_SkillBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ARKGASCharacterPlayer* TargetCharacter = Cast<ARKGASCharacterPlayer>(ActorInfo->AvatarActor.Get());
	if (TargetCharacter)
	{
		TargetCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void URKGA_SkillBase::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);

}

void URKGA_SkillBase::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);

}
