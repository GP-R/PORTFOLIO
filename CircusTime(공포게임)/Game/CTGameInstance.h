// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CTGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUSTIME_API UCTGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCTGameInstance();

public:
	UFUNCTION(BlueprintCallable)
	void ChangeLevel(FName NewLevelName);

protected:
	virtual void Init() override;

};
