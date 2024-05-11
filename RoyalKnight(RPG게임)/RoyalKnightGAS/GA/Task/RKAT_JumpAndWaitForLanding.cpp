#include "GA/Task/RKAT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

URKAT_JumpAndWaitForLanding::URKAT_JumpAndWaitForLanding()
{
}

URKAT_JumpAndWaitForLanding* URKAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	URKAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<URKAT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void URKAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.AddDynamic(this, &URKAT_JumpAndWaitForLanding::OnLandedCallback);
	Character->Jump();

	SetWaitingOnAvatar();
}

void URKAT_JumpAndWaitForLanding::OnDestroy(bool AbilityEnded)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &URKAT_JumpAndWaitForLanding::OnLandedCallback);

	Super::OnDestroy(AbilityEnded);
}

void URKAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}
