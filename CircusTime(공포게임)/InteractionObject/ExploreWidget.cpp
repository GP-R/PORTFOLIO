#include "InteractionObject/ExploreWidget.h"

#include "Components/TextBlock.h"

void UExploreWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UExploreWidget::SetExploreWidget(FText NewName, FText NewDescription)
{
	Name->SetText(NewName);
	Description->SetText(NewDescription);
}