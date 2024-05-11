// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMaskWidget.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API USelectMaskWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	TArray<UTexture2D*> GetMaskImageArray();

	UFUNCTION()
	void AddMaskImage(UTexture2D* Image);

	UFUNCTION()
	void RemoveMaskImage(UTexture2D* Image);

	UFUNCTION()
	void ChangeMaskImage(int32 Index);

	UFUNCTION()
	void Successed();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayEndMaskGameCinematic();

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnLeftSelectBodyButtonClicked();

	UFUNCTION()
	void OnRightSelectBodyButtonClicked();

	UFUNCTION()
	void OnLeftSelectMaskButtonClicked();

	UFUNCTION()
	void OnRightSelectMaskButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

	UFUNCTION()
	void CameraMove(AActor* ActorToMove, class AMaskGameBodyActor* Target, float Duration);

public:
	UPROPERTY(VisibleAnywhere)
	FTimerHandle MoveTimerHandle;

	UPROPERTY(meta = (BindWidget))
	class UImage* MaskImage;

	UPROPERTY()
	int32 CurVisibleImageIndex;

	UPROPERTY()
	UTexture2D* EmptyMaskImage;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* LeftSelectBodyButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RightSelectBodyButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* LeftSelectMaskButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RightSelectMaskButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectMaskText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SuccessText;

	UPROPERTY(VisibleAnywhere)
	TArray<UTexture2D*> MaskImageArray;
	
	UPROPERTY(VisibleAnywhere)
	bool bCameraMoving;

	FTimerDelegate TimerDel;

	FTimerHandle ExitGame;
};
