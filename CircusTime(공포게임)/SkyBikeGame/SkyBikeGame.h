// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkyBikeGame.generated.h"

UCLASS()
class CIRCUSTIME_API ASkyBikeGame : public AActor
{
	GENERATED_BODY()
	
public:
	ASkyBikeGame();

	UFUNCTION()
	void SpawnAndPosessSkyBikePawn();

	UFUNCTION()
	void FailSkyBikeGame();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void InteractStartLadder();

	UFUNCTION()
	void InteractEndLadder();

	UFUNCTION()
	void InteractSkyBike();

	UFUNCTION()
	void TeleportToStartFloor();

	UFUNCTION()
	void TeleportToEndFloor();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* StartLadder;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* EndLadder;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* SkyBike;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class USceneComponent* RootMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* StartTeleportFloor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class USceneComponent* EndTeleportFloor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class USceneComponent* EndLadderTeleportPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class USceneComponent* SkyBikeStartPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class USceneComponent* SkyBikeEndPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class USceneComponent* ClearGameTeleportLocation;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASkyBikePawn> SkyBikePawnClass;

	UPROPERTY()
	class ASkyBikePawn* SkyBikePawn;

	UPROPERTY()
	class ACTPlayerController* PlayerController;
};
