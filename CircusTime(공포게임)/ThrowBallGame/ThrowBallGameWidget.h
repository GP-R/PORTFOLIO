// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ThrowBallGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API UThrowBallGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(class AThrowBallGame* ThrowBallGameInstance);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ThrowPowerBar;

	class AThrowBallGame* ThrowBallGame;
};
