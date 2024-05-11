#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ClearWayPoint.generated.h"

UCLASS()
class CIRCUSTIME_API UBTTaskNode_ClearWayPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_ClearWayPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
