#include "AI/BTTaskNode_ClearWayPoint.h"
#include "AI/CTAIController.h"
#include "Character/CTBossCharacter.h"

UBTTaskNode_ClearWayPoint::UBTTaskNode_ClearWayPoint()
{
	NodeName = TEXT("ClearWayPoint");
}

EBTNodeResult::Type UBTTaskNode_ClearWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACTBossCharacter* Boss = Cast<ACTBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Boss->SetCurWayPoint(nullptr);
	return EBTNodeResult::Succeeded;
}