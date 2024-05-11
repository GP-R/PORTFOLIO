// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveMeshComponent.h"
#include "MoleGame/MoleGame.h"
#include "Mole.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API UMole : public UInteractiveMeshComponent
{
	GENERATED_BODY()
	
public:
	UMole();

	UFUNCTION()
	void Init(AMoleGame* NewMoleGame);

	UFUNCTION()
	bool RiseAndFall();

	UFUNCTION()
	bool ChangeMoleState(bool bRedMole);

	UFUNCTION()
	bool IsRising() const { return bIsRising; }

	UFUNCTION()
	void Clear();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHammer> Hammer;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void InteractMole();

	UFUNCTION()
	void Rise();

	UFUNCTION()
	void Fall();
private:
	UPROPERTY(EditAnywhere)
	AMoleGame* MoleGame;

	uint8 bIsRising : 1;
	uint8 bIsRedMole : 1;
	float MoveSpeed;
	FVector OriginalPosition;
	float StopTime;

	FScriptDelegate MoleInteractDelegate;
	FTimerHandle RiseTimer;
	FTimerHandle FallTimer;

	UMaterialInterface* OriginalMaterial;
	UMaterialInterface* RedMoleMaterial;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* CatchRedMoleEffect;
	UParticleSystem* CatchMoleEffect;
};
