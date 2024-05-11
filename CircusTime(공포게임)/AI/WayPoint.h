#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WayPoint.generated.h"

UCLASS()
class CIRCUSTIME_API AWayPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AWayPoint();

	UFUNCTION()
	AWayPoint* GetNextWayPoint() { return NextWayPoint; }

	UFUNCTION()
	AWayPoint* GetPrevWayPoint() { return PrevWayPoint; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	AWayPoint* NextWayPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	AWayPoint* PrevWayPoint;
};
