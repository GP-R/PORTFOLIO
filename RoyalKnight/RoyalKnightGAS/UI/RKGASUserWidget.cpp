#include "UI/RKGASUserWidget.h"
#include "AbilitySystemBlueprintLibrary.h"

void URKGASUserWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	if (IsValid(InOwner))
	{
		ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
	}
}

UAbilitySystemComponent* URKGASUserWidget::GetAbilitySystemComponent() const
{
	return ASC;
}
