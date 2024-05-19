// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExploreWidget.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API UExploreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetExploreWidget(FText NewName, FText NewDescription);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Description;
};
