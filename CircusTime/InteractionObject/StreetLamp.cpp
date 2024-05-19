#include "InteractionObject/StreetLamp.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"

AStreetLamp::AStreetLamp()
{
	PrimaryActorTick.bCanEverTick = true;
	StreetLampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StreetLamp"));
	SetRootComponent(StreetLampMesh);

	/*LeftLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LeftLight"));
	LeftLight->SetupAttachment(StreetLampMesh);

	RightLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RightLight"));
	RightLight->SetupAttachment(StreetLampMesh);*/

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(StreetLampMesh);

	bBlinkEffect = false;
}

void AStreetLamp::BeginPlay()
{
	Super::BeginPlay();
	if (!bBlinkEffect)
	{
		SetLightsVisible(false);
	}
}

void AStreetLamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStreetLamp::SetLightsVisible(bool bIsTurnOn)
{
	/*if (LeftLight == nullptr || RightLight == nullptr)
	{
		return;
	}

	LeftLight->SetVisibility(bIsTurnOn);
	RightLight->SetVisibility(bIsTurnOn);*/

	SpotLight->SetVisibility(bIsTurnOn);
}