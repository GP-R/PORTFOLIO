// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoleGame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCatchMoleDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoleGameFailDelegate);

UCLASS()
class CIRCUSTIME_API AMoleGame : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoleGame();

	UFUNCTION(BlueprintCallable)
	int GetCatchMoleCount() { return CatchMoleCount; }

	UFUNCTION(BlueprintCallable)
	void SetCatchMoleCount(int Count) { CatchMoleCount  = Count; }

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetBloodWidget() { return BloodWidget; }

	UFUNCTION(BlueprintCallable)
	class UInteractiveMeshComponent* GetMoleMachine() { return MoleMachine; }

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void InteractMoleMachine();

	UFUNCTION()
	void RiseRandomMole();

	UFUNCTION()
	void Fail();

	UFUNCTION()
	void Clear();

public:
	UPROPERTY(BlueprintAssignable)
	FCatchMoleDelegate CatchMoleEvent;

	UPROPERTY(BlueprintAssignable)
	FMoleGameFailDelegate MoleGameFailEvent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> BloodWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UUserWidget* BloodWidget;

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* MoleMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<class UMole*> MoleArray;

	UPROPERTY(VisibleAnywhere)
	int8 MoleCount = 8;

	UPROPERTY(VisibleAnywhere)
	class ACTPlayerCharacter* Player;

	UPROPERTY(VisibleAnywhere)
	int CatchMoleCount;

	float TimeSinceLastSpawn = 0.0f;

	UPROPERTY(EditAnywhere)
	float RedMoleSpawnInterval = 2.0f;

	FTimerHandle MoleRiseTimer;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	USceneComponent* StartTransfrom;
};
