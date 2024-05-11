#include "FindMaskGame/MaskGameBodyActor.h"
#include "FindMaskGame/MaskGameMaskActor.h"
#include "FindMaskGame/SelectMaskPawn.h"
#include "FindMaskGame/SelectMaskWidget.h"
#include "InteractiveMeshComponent.h"
#include "CTPlayerController.h"

#include "Kismet/GameplayStatics.h"

AMaskGameBodyActor::AMaskGameBodyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootEmptyComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EmptyComponent"));
	SetRootComponent(RootEmptyComponent);

	BodyMesh = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootEmptyComponent);

	BodyCameraPosition = CreateDefaultSubobject<USceneComponent>(TEXT("BodyCameraPosition"));
	BodyCameraPosition->SetupAttachment(RootEmptyComponent);

}

void AMaskGameBodyActor::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate BodyMeshInteract;
	BodyMeshInteract.BindUFunction(this, "InteractBody");
	BodyMesh->OnInteract.Add(BodyMeshInteract);
	BodyMesh->SetInteractLockState(false);
}

void AMaskGameBodyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaskGameBodyActor::InteractBody()
{
	ACTPlayerController* CTPlayerController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CTPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}

	CTPlayerController->SetActiveCTPlayer(false);

	ASelectMaskPawn* SelectMaskPawn = Cast<ASelectMaskPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASelectMaskPawn::StaticClass()));
	SelectMaskPawn->SetActorRelativeRotation(BodyCameraPosition->GetComponentRotation());
	SelectMaskPawn->SetActorRelativeLocation(BodyCameraPosition->GetComponentLocation());

	CTPlayerController->Possess(SelectMaskPawn);

	SelectMaskPawn->SetCurrentSelectedBody(this);
}

