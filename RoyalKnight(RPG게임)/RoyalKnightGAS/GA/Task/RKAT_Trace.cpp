#include "GA/Task/RKAT_Trace.h"
#include "GA/TargetActor/RKTA_Trace.h"
#include "AbilitySystemComponent.h"

URKAT_Trace::URKAT_Trace()
{
}

URKAT_Trace* URKAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class ARKTA_Trace> TargetActorClass)
{
	URKAT_Trace* NewTask = NewAbilityTask<URKAT_Trace>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void URKAT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void URKAT_Trace::OnDestroy(bool AbilityEnded)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}

	Super::OnDestroy(AbilityEnded);
}

void URKAT_Trace::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<ARKTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->SetShowDebug(true);
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &URKAT_Trace::OnTargetDataReadyCallback);
	}
}

void URKAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		// 입력으로 지연 가능
		SpawnedTargetActor->ConfirmTargeting();
	}
}

void URKAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}
