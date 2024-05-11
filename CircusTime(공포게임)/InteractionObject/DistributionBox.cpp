#include "InteractionObject/DistributionBox.h"
#include "InteractiveMeshComponent.h"
#include "InteractionObject/StreetLamp.h"

#include "Engine/StaticMeshActor.h"
ADistributionBox::ADistributionBox()
{
	PrimaryActorTick.bCanEverTick = true;
	Distribution = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("Distribution"));
	SetRootComponent(Distribution);

	Lever = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("Lever"));
	Lever->SetupAttachment(Distribution);
}

void ADistributionBox::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate InteractLeverEvent;
	InteractLeverEvent.BindUFunction(this, "InteractLever");
	Lever->OnInteract.Add(InteractLeverEvent);

	if (HallLight)
	{
		HallLight->GetStaticMeshComponent()->SetVisibility(false);
	}
	if (HallFrontLight)
	{
		HallFrontLight->GetStaticMeshComponent()->SetVisibility(false);
	}

	for (AStreetLamp* Lamp : FirstTurnOnLight)
	{
		Lamp->SetLightsVisible(false);
	}
	for (AStreetLamp* Lamp : SecondTurnOnLight)
	{
		Lamp->SetLightsVisible(false);
	}
	for (AStreetLamp* Lamp : ThirdTurnOnLight)
	{
		Lamp->SetLightsVisible(false);
	}
}

void ADistributionBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADistributionBox::InteractLever()
{
	UE_LOG(LogTemp, Log, TEXT("Interact Lever"));
	//GetWorld()->GetTimerManager().SetTimer(LeverDelayTimer, this, &ADistributionBox::TurnOnLights, MovingLeverTimelineLength, false);

}

void ADistributionBox::TurnOnLights(TArray<AStreetLamp*> Lights)
{
	for (AStreetLamp* Lamp : Lights)
	{
		Lamp->SetLightsVisible(true);
	}
}
