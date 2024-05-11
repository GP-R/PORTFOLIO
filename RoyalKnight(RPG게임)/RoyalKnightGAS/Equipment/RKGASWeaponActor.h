// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/RKGASEquipment.h"
#include "RKGASWeaponActor.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API ARKGASWeaponActor : public ARKGASEquipment
{
	GENERATED_BODY()
	
public:	
	ARKGASWeaponActor();

	virtual void Equip(AActor* Target, FName SocketName) override;

	FORCEINLINE TArray<TSubclassOf<class URKGA_SkillBase>> GetSkillAbilityClasses() { return SkillAbilityClasses; }

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class URKGA_SkillBase>> SkillAbilityClasses;
};
