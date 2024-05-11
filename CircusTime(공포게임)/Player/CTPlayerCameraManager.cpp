#include "CTPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "CTPlayerCharacter.h"
#include "CTPlayerWidget.h"

ACTPlayerCameraManager::ACTPlayerCameraManager()
{

}
//TODO : Delegate이용해서 끝날때 BroadCast하도록 만들기
void ACTPlayerCameraManager::AsyncCameraFade(float Time, TFunction<void(void)>&& Callback)
{
	StartCameraFade(0.0f, 1.0f, Time, FLinearColor::Black, false, true);

	ACTPlayerCharacter* Player = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->DisablePlayerInput(false);
	}
	FadeCallback = MoveTemp(Callback);
	GetWorld()->GetTimerManager().SetTimer(CameraFadeInTimerHandle, this, &ACTPlayerCameraManager::ExecuteFadeInCallback, Time, false);
}

void ACTPlayerCameraManager::ExecuteFadeInCallback()
{
	if (FadeCallback)
	{
		FadeCallback();
		GetWorld()->GetTimerManager().SetTimer(CameraFadeOutTimerHandle, this, &ACTPlayerCameraManager::ExecuteFadeOutCallback, 1.f, false);
	}
}

void ACTPlayerCameraManager::ExecuteFadeOutCallback()
{
	StartCameraFade(1.0f, 0.0f, Delay, FLinearColor::Black, false, true);
	ACTPlayerCharacter* Player = Cast< ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->EnablePlayerInput();
	}
}
