#include "UI/RKGASWidgetComponent.h"
#include "UI/RKGASUserWidget.h"

void URKGASWidgetComponent::InitWidget()
{
	Super::InitWidget();

	URKGASUserWidget* GASUserWidget = Cast<URKGASUserWidget>(GetWidget());
	if (GASUserWidget)
	{
		GASUserWidget->SetAbilitySystemComponent(GetOwner());
	}
}

