#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanMove.generated.h"

UCLASS()
class CIRCUSTIME_API UBTDecorator_CanMove : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_CanMove();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
