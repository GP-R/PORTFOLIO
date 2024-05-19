// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaskGameBodyActor.generated.h"

UCLASS()
class CIRCUSTIME_API AMaskGameBodyActor : public AActor
{
	GENERATED_BODY()

public:
	AMaskGameBodyActor();

	UFUNCTION()
	class UInteractiveMeshComponent* GetBodyMesh() { return BodyMesh; }

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void InteractBody();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AMaskGameBodyActor* NextBodyActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AMaskGameBodyActor* PrevBodyActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AMaskGameMaskActor* CorrectMask;

	UPROPERTY(EditAnywhere)
	UStaticMesh* CorrectBody;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* BodyCameraPosition;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class USceneComponent* RootEmptyComponent;


};
