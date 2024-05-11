// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SkyBikePawn.generated.h"

UCLASS()
class CIRCUSTIME_API ASkyBikePawn : public APawn
{
	GENERATED_BODY()

public:
	ASkyBikePawn();

	UFUNCTION()
	void Init(FVector StartPosition, FVector Destination, class ASkyBikeGame* InSkyBikeGame);

	UFUNCTION()
	void DestroyFireEffects();

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySkyBikeCinematic();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class USkeletalMeshComponent* BikeMesh;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class ASkyBikeGame* SkyBikeGame;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* ParticleEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* LeftFallDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* RightFallDown;

private:
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void RotatePitch(float Value);

	UFUNCTION()
	void ToggleDirection();

	UFUNCTION(BlueprintCallable)
	void ReSet();

private:
	UPROPERTY()
	FVector StartPosition;

	UPROPERTY()
	FVector Destination;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	FTimerHandle ToggleTimerHandle;

	UPROPERTY()
	bool bRotateLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float AnimPitch = 0.0f;
	
	float TimeSinceLastSpawn = 0.0f;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 0.3f;

	TArray<class UNiagaraComponent*> SpawnedEffects;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float RotationSpeed = 20.0f;
};
