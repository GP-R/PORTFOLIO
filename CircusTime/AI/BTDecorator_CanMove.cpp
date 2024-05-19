#include "AI/BTDecorator_CanMove.h"
#include "AI/CTAIController.h"
#include "Character/CTBossCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanMove::UBTDecorator_CanMove()
{
	NodeName = TEXT("CanMove");
}

bool UBTDecorator_CanMove::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACTBossCharacter* Boss = Cast<ACTBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		return false;
	}

	return Boss->GetCanMove();
}