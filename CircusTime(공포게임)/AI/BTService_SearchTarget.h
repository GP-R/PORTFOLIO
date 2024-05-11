#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchTarget.generated.h"

UCLASS()
class CIRCUSTIME_API UBTService_SearchTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SearchTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
