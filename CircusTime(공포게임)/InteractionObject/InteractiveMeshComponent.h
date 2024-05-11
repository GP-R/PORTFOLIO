// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveMeshComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHighLightDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndHighLightDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractDelegate);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CIRCUSTIME_API UInteractiveMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UInteractiveMeshComponent();

	UPROPERTY(BlueprintAssignable)
	FHighLightDelegate OnHighLight;

	UPROPERTY(BlueprintAssignable)
	FEndHighLightDelegate OnEndHighLight;

	UPROPERTY(BlueprintAssignable)
	FInteractDelegate OnInteract;

	UFUNCTION()
	void HighLightMesh();

	UFUNCTION()
	void EndHighLightMesh();

	UFUNCTION(BlueprintGetter)
	bool GetInteractLockState();

	UFUNCTION(BlueprintSetter)
	void SetInteractLockState(bool bValue);

private:
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Meta = (AllowPrivateAccess = true, BlueprintGetter = "GetInteractLockState", BlueprintSetter = "SetInteractLockState"))
	bool bInteractLock;
};
