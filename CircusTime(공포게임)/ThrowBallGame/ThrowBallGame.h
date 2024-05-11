// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowBallGame.generated.h"

UCLASS()
class CIRCUSTIME_API AThrowBallGame : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowBallGame();

	UFUNCTION()
	float GetThrowPower() { return ThrowPower; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void InteractMachine();

	UFUNCTION()
	void SetThrowPower();

	UFUNCTION()
	void ThrowBall();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* GameMachine;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	USceneComponent* StartTransfrom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UThrowBallGameWidget> GameWidgetSubClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UThrowBallGameWidget* GameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ThrowBallAnim;

	UPROPERTY()
	float ThrowPower = 0.0f;

	UPROPERTY()
	float ThrowPowerChangeRate = 1.0f;

	bool bCanThrow = false;
};
