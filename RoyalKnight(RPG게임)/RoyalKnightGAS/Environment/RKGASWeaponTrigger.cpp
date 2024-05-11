#include "Environment/RKGASWeaponTrigger.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Tag/RKGameplayTag.h"
#include "Character/RKGASCharacterPlayer.h"

void ARKGASWeaponTrigger::NotifyActorBeginOverlap(AActor* Other)
{
	Super::NotifyActorBeginOverlap(Other);
	/*ARKGASCharacterPlayer* Player = Cast<ARKGASCharacterPlayer>(Other);
	if (Player)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Other, RKTAG_EVENT_CHARACTER_WEAPONUNEQUIP, FGameplayEventData());
		Player->SetWeaponClass(WeaponClass);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Other, RKTAG_EVENT_CHARACTER_WEAPONEQUIP, FGameplayEventData());
	}*/
	
}
