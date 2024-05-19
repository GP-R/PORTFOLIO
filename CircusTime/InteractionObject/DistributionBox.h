// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DistributionBox.generated.h"

UCLASS()
class CIRCUSTIME_API ADistributionBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ADistributionBox();

	UFUNCTION(BlueprintCallable)
	void TurnOnLights(TArray<class AStreetLamp*> Lights);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void InteractLever();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* Distribution;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* Lever;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float MovingLeverTimelineLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class AStaticMeshActor* HallLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class AStaticMeshActor* HallFrontLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<class AStreetLamp*> FirstTurnOnLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<class AStreetLamp*> SecondTurnOnLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<class AStreetLamp*> ThirdTurnOnLight;

};
