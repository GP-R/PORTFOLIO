// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API UCTPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractText;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;

	class ACTPlayerCharacter* Player;

public:
	class UTextBlock* GetInteractText();

	UFUNCTION(BlueprintCallable)
	void SetVisibleInteractText(bool bVisible);
};
