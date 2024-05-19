#include "FindMaskGame/MaskGameMaskActor.h"
#include "FindMaskGame/SelectMaskWidget.h"
#include "FindMaskGame/SelectMaskPawn.h"
#include "InteractiveMeshComponent.h"

#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"

AMaskGameMaskActor::AMaskGameMaskActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MaskMesh = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("MaskMesh"));

	SetRootComponent(MaskMesh);
}

void AMaskGameMaskActor::BeginPlay()
{
	Super::BeginPlay();
	
	FScriptDelegate MaskMeshInteract;
	MaskMeshInteract.BindUFunction(this, "InteractMask");
	MaskMesh->OnInteract.Add(MaskMeshInteract);
	MaskMesh->SetInteractLockState(false);

}

void AMaskGameMaskActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaskGameMaskActor::InteractMask()
{
	ASelectMaskPawn* SelectMaskPawn = Cast<ASelectMaskPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASelectMaskPawn::StaticClass()));
	SelectMaskPawn->GetMaskGameWidget()->AddMaskImage(MaskImage);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

