// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API ACTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACTPlayerController();

	UFUNCTION(BlueprintCallable)
	void SetActiveCTPlayer(bool bIsActive);

	UFUNCTION()
	void PossessedDefaultPawn();

	UFUNCTION(BlueprintCallable)
	class UDialogueController* GetDialogueController() { return DialogueController; }

	UFUNCTION(BlueprintCallable)
	class UAudioComponent* GetAudioComponent() { return AudioComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void NextDialogue();

	UFUNCTION()
	void TogglePauseMenuWidget();

private:
	UPROPERTY(VisibleAnywhere)
	class UDialogueController* DialogueController;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UUserWidget* PauseMenuWidget;
};
