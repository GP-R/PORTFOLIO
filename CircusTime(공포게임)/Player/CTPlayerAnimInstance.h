// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CTPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API UCTPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;
};
