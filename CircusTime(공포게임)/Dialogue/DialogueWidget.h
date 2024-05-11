// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogueText;

	FString TypingText;
	int CurTextIndex;
	FTimerHandle TypingEffect;

public:
	UFUNCTION()
	class UTextBlock* GetDialogueText();

	UFUNCTION()
	void SetDialogueText(FText Text);

	UFUNCTION()
	void PlayTextTypingEffect(FText Text, float VoiceTime);

	UFUNCTION()
	void SetActiveDialogueUI(bool bActive);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void EndTypingTextEffect();

private:
	UFUNCTION()
	void AddNextCharacter();
};
