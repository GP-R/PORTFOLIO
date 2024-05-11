#include "Equipment/RKGASWeaponActor.h"
#include "AbilitySystemComponent.h"
#include "GA/RKGA_SkillBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/RKGASCharacterPlayer.h"
#include "Player/RKGASPlayerController.h"
#include "UI/RKGASHUDWidget.h"

ARKGASWeaponActor::ARKGASWeaponActor()
{

}

void ARKGASWeaponActor::Equip(AActor* Target, FName SocketName)
{
	Super::Equip(Target, SocketName);

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	{
		for (TSubclassOf<URKGA_SkillBase>& SkillAbilityClass : SkillAbilityClasses)
		{
			FGameplayAbilitySpec NewSkillSpec(SkillAbilityClass);
			NewSkillSpec.InputID = SkillAbilityClass.GetDefaultObject()->GetInputID();

			if (!TargetASC->FindAbilitySpecFromClass(SkillAbilityClass))
			{
				TargetASC->GiveAbility(NewSkillSpec);
				ARKGASCharacterPlayer* Temp = Cast<ARKGASCharacterPlayer>(Target);

				ARKGASPlayerController* PlayerController = Cast<ARKGASPlayerController>(Temp->GetController());
				if (PlayerController)
				{
					URKGASHUDWidget* HUD = PlayerController->GetHUD();
					if (HUD)
					{
						HUD->UpdateSkillIcon(SkillAbilityClass.GetDefaultObject()->GetSkillIcon(), SkillAbilityClass.GetDefaultObject()->GetInputID());

					}
				}

			}
		}

	}
}
