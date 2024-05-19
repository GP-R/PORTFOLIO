// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment/RKGASTriggerBox.h"
#include "RKGASWeaponTrigger.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API ARKGASWeaponTrigger : public ARKGASTriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* Other) override;

protected:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class ARKGASWeaponActor> WeaponClass;

};
