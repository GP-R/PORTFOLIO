#pragma once

#include "CoreMinimal.h"
#include "Character/RKCharacterEnemy.h"
#include "AbilitySystemInterface.h"
#include "RKGASCharacterEnemy.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API ARKGASCharacterEnemy : public ARKCharacterEnemy, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ARKGASCharacterEnemy();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	virtual void OnOutOfHealth();

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class URKCharacterAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayEffect> InitStatEffect;

	UPROPERTY(EditAnywhere, Category = GAS)
	float Level;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class URKGASWidgetComponent> HpBar;
};
