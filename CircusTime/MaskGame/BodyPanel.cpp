#include "InteractiveMeshComponent.h"
#include "MaskGame/BodyPanel.h"
#include "MaskGame/MaskGameMaskActor.h"
#include "MaskGame/SelectMaskPawn.h"

#include "Kismet/GameplayStatics.h"

ABodyPanel::ABodyPanel()
{
	BodyMeshComponent = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("BodyMeshComponent"));
	SetRootComponent(BodyMeshComponent);

	CameraPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPosition"));
	CameraPosition->SetupAttachment(BodyMeshComponent);
}

void ABodyPanel::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate InteractedEvent;

	InteractedEvent.BindUFunction(this, "Interacted");
	BodyMeshComponent->OnInteract.Add(InteractedEvent);
	BodyMeshComponent->SetInteractLockState(false);
}

void ABodyPanel::Interacted()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator Rotator = CameraPosition->GetComponentRotation();
	FVector SpawnLocation = CameraPosition->GetComponentLocation();

	if (SelectMaskPawnBP != nullptr)
	{
		ASelectMaskPawn* SelectMaskPawn = GetWorld()->SpawnActor<ASelectMaskPawn>(SelectMaskPawnBP, SpawnLocation, Rotator, SpawnParams);
		SelectMaskPawn->SetCurrentSelectedBody(this);
	}

	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(PC))
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}
	PC->Possess(SelectMaskPawn);
}

void ABodyPanel::CombineMask()
{
	BodyMeshComponent->SetStaticMesh(CorrectBody);
}