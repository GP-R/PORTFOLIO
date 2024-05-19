// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaskGameMaskActor.generated.h"

UCLASS()
class CIRCUSTIME_API AMaskGameMaskActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMaskGameMaskActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void InteractMask();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UTexture2D* MaskImage;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* MaskMesh;

};
