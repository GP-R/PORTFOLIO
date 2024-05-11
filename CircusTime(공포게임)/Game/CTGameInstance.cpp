// Fill out your copyright notice in the Description page of Project Settings.


#include "CTGameInstance.h"
#include "CTPlayerCharacter.h"

#include "Kismet/GameplayStatics.h"

UCTGameInstance::UCTGameInstance()
{
}

void UCTGameInstance::Init()
{
    Super::Init();

}

void UCTGameInstance::ChangeLevel(FName NewLevelName)
{
    if (NewLevelName != NAME_None)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(World, 0);
            if (CameraManager)
            {
                float FadeOutDuration = 1.0f;
                CameraManager->StartCameraFade(0.0f, 1.0f, FadeOutDuration, FLinearColor::Black, false, true);

                ACTPlayerCharacter* Player = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
                if (Player)
                {
                    Player->DisablePlayerInput(false);
                    //Player->GetPlayerWidget()->SetVisibility(ESlateVisibility::Hidden);
                }
                FTimerDelegate LoadLevelDelegate;
                FTimerHandle FadeOutTimerHandle;
                LoadLevelDelegate.BindLambda([this, NewLevelName, &FadeOutTimerHandle]()
                    {
                        GetTimerManager().ClearTimer(FadeOutTimerHandle);
                        UGameplayStatics::OpenLevel(GetWorld(), NewLevelName);
                    });

                World->GetTimerManager().SetTimer(FadeOutTimerHandle, LoadLevelDelegate, FadeOutDuration, false);
            }
        }
    }
}
