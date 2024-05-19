// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/DialogueWidget.h"
#include "Components/TextBlock.h"


UTextBlock* UDialogueWidget::GetDialogueText()
{
	return DialogueText;
}

void UDialogueWidget::SetDialogueText(FText Text)
{
	if (DialogueText)
	{
		DialogueText->SetText(Text);
	}
}

void UDialogueWidget::PlayTextTypingEffect(FText Text, float VoiceTime)
{
	TypingText = Text.ToString();
	CurTextIndex = 0;

	float TimePerCharacter = VoiceTime / (float)TypingText.Len();

	GetWorld()->GetTimerManager().SetTimer(TypingEffect, this, &UDialogueWidget::AddNextCharacter, TimePerCharacter, true);
}

void UDialogueWidget::AddNextCharacter()
{
	if (CurTextIndex < TypingText.Len())
	{
		FString CurText = TypingText.Mid(0, CurTextIndex + 1);
		DialogueText->SetText(FText::FromString(CurText));
		++CurTextIndex;
	}
	else
	{
		EndTypingTextEffect();
	}
}

void UDialogueWidget::EndTypingTextEffect()
{
	DialogueText->SetText(FText::FromString(TypingText));
	GetWorld()->GetTimerManager().ClearTimer(TypingEffect);
}

void UDialogueWidget::SetActiveDialogueUI(bool bActive)
{
	if (bActive)
	{
		DialogueText->SetText(FText::GetEmpty());
		this->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply UDialogueWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Log, TEXT("UI Click"));
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}