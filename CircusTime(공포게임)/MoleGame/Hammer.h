#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoleGame/MoleGame.h"
#include "Hammer.generated.h"

UCLASS()
class CIRCUSTIME_API AHammer : public AActor
{
	GENERATED_BODY()
	
public:	
	AHammer();

	UFUNCTION()
	void Init(AMoleGame* NewMoleGame);

	UFUNCTION(BlueprintNativeEvent)
	void Hit();
	virtual void Hit_Implementation();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	AMoleGame* MoleGame;
};
