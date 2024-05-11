#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemInterface.h"
#include "RKGASUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API URKGASUserWidget : public UUserWidget, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual void SetAbilitySystemComponent(AActor* InOwner);
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
};
