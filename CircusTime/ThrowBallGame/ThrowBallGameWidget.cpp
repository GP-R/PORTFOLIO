#include "ThrowBallGame/ThrowBallGameWidget.h"
#include "ThrowBallGame/ThrowBallGame.h"

#include "Components/ProgressBar.h"


void UThrowBallGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ThrowPowerBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ThrowPowerBar")));

}

void UThrowBallGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	ThrowPowerBar->SetPercent(ThrowBallGame->GetThrowPower() / 100.0f);
}

void UThrowBallGameWidget::Init(AThrowBallGame* ThrowBallGameInstance)
{
	ThrowBallGame = ThrowBallGameInstance;
}