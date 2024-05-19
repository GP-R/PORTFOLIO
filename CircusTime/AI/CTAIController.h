#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CTAIController.generated.h"

UCLASS()
class CIRCUSTIME_API ACTAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACTAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY()
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UBlackboardData* BlackboardData;
};
