#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StreetLamp.generated.h"

UCLASS()
class CIRCUSTIME_API AStreetLamp : public AActor
{
	GENERATED_BODY()
	
public:	
	AStreetLamp();

	UFUNCTION(BlueprintCallable)
	void SetLightsVisible(bool bIsTurnOn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlinkEffect;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* StreetLampMesh;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class USpotLightComponent* SpotLight;

	/*UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class UPointLightComponent* LeftLight;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class UPointLightComponent* RightLight;*/
}; 
