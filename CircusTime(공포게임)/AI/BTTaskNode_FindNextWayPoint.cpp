#include "AI/BTTaskNode_FindNextWayPoint.h"
#include "AI/CTAIController.h"
#include "AI/WayPoint.h"
#include "Character/CTBossCharacter.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTaskNode_FindNextWayPoint::UBTTaskNode_FindNextWayPoint()
{
	NodeName = TEXT("FindNextWayPoint");
}

EBTNodeResult::Type UBTTaskNode_FindNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACTBossCharacter* Boss = Cast<ACTBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Boss == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// TargetOnµÇ¸é Boss CurWayPoint = nulltpr
	AWayPoint* CurWayPoint = Boss->GetCurWayPoint();
	if (CurWayPoint == nullptr)
	{
		TArray<AActor*> WayPoints;
		UGameplayStatics::GetAllActorsOfClass(Boss->GetWorld(), AWayPoint::StaticClass(), WayPoints);
		float MinDistance = MAX_FLT;
		if (WayPoints.Num() == 0)
		{
			return EBTNodeResult::Failed;
		}
		for (AActor* WayPoint : WayPoints)
		{
			float Distance = FVector::Dist(Boss->GetActorLocation(), WayPoint->GetActorLocation());
			if (MinDistance > Distance)
			{
				MinDistance = Distance;
				CurWayPoint = Cast<AWayPoint>(WayPoint);
				Boss->SetCurWayPoint(CurWayPoint);
			}
		}
		FVector NewVector = CurWayPoint->GetActorLocation();
		NewVector.Z = Boss->GetActorLocation().Z;
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), NewVector);
		return EBTNodeResult::Succeeded;
	}

	if (CurWayPoint->GetNextWayPoint() == nullptr && CurWayPoint->GetPrevWayPoint() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Boss->SetCurWayPoint(CurWayPoint->GetNextWayPoint() != nullptr ? CurWayPoint->GetNextWayPoint() : CurWayPoint->GetPrevWayPoint());
	FVector NewVector = Boss->GetCurWayPoint()->GetActorLocation();
	NewVector.Z = Boss->GetActorLocation().Z;
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), NewVector);
	
	return EBTNodeResult::Succeeded;
}