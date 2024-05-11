// Fill out your copyright notice in the Description page of Project Settings.


#include "CTPlayerWidget.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "CTPlayerCharacter.h"

void UCTPlayerWidget::NativeConstruct()
{
    Super::NativeConstruct();
    Player = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    InteractText = Cast<UTextBlock>(GetWidgetFromName(TEXT("InteractText")));
    StaminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));

    InteractText->SetVisibility(ESlateVisibility::Hidden);
}

void UCTPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    ACTPlayerCharacter* temp = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (temp)
    {
        StaminaBar->SetPercent(temp->GetStaminaValue() / 100.0f);
    }
}

UTextBlock* UCTPlayerWidget::GetInteractText()
{
    return InteractText;
}

void UCTPlayerWidget::SetVisibleInteractText(bool bVisible)
{
    if (bVisible)
    {
        InteractText->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        InteractText->SetVisibility(ESlateVisibility::Hidden);
    }
}