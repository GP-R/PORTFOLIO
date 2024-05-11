#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindNextWayPoint.generated.h"

UCLASS()
class CIRCUSTIME_API UBTTaskNode_FindNextWayPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_FindNextWayPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
