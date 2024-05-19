// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyBikeGame/SkyBikeGame.h"
#include "SkyBikeGame/SkyBikePawn.h"
#include "InteractiveMeshComponent.h"
#include "CTPlayerCameraManager.h"
#include "CTPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

ASkyBikeGame::ASkyBikeGame()
{
	PrimaryActorTick.bCanEverTick = false;

	StartLadder = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("StartLadder"));
	EndLadder = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("EndLadder"));
	SkyBike = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("SkyBike"));

	RootMeshComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootMeshComponent"));
	StartTeleportFloor = CreateDefaultSubobject<USceneComponent>(TEXT("StartTeleportFloor"));
	EndTeleportFloor = CreateDefaultSubobject<USceneComponent>(TEXT("EndTeleportFloor"));
	SkyBikeStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SkyBikeStartPosition"));
	SkyBikeEndPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SkyBikeEndPosition"));
	ClearGameTeleportLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ClearGameTeleportLocation"));
	SetRootComponent(RootMeshComponent);

	StartLadder->SetupAttachment(RootMeshComponent);
	EndLadder->SetupAttachment(RootMeshComponent);
	SkyBike->SetupAttachment(RootMeshComponent);

	StartTeleportFloor->SetupAttachment(RootMeshComponent);
	EndTeleportFloor->SetupAttachment(RootMeshComponent);
	ClearGameTeleportLocation->SetupAttachment(RootMeshComponent);

	SkyBikeStartPosition->SetupAttachment(RootMeshComponent);
	SkyBikeEndPosition->SetupAttachment(RootMeshComponent);

	static ConstructorHelpers::FClassFinder<ASkyBikePawn> SkyBikePawnBP(TEXT("Blueprint'/Game/Blueprints/Character/SkyBike/BP_SkyBikePawn.BP_SkyBikePawn_C'"));
	if (SkyBikePawnBP.Succeeded())
	{
		SkyBikePawnClass = SkyBikePawnBP.Class;
	}
}

void ASkyBikeGame::BeginPlay()
{
	Super::BeginPlay();
	
	FScriptDelegate StartLadderInteract;
	StartLadderInteract.BindUFunction(this, "InteractStartLadder");
	StartLadder->OnInteract.Add(StartLadderInteract);
	StartLadder->SetInteractLockState(false);

	FScriptDelegate EndLadderInteract;
	EndLadderInteract.BindUFunction(this, "InteractEndLadder");
	EndLadder->OnInteract.Add(EndLadderInteract);

	FScriptDelegate SkyBikeInteract;
	SkyBikeInteract.BindUFunction(this, "InteractSkyBike");
	SkyBike->OnInteract.Add(SkyBikeInteract);
	SkyBike->SetInteractLockState(false);

	PlayerController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}
}

void ASkyBikeGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkyBikeGame::InteractStartLadder()
{
	ACTPlayerCameraManager* CameraManager = Cast<ACTPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	if (CameraManager)
	{
		CameraManager->AsyncCameraFade(1.0f, [this]() { TeleportToStartFloor(); });
	}
	StartLadder->SetInteractLockState(true);
	EndLadder->SetInteractLockState(false);
}

void ASkyBikeGame::InteractEndLadder()
{
	ACTPlayerCameraManager* CameraManager = Cast<ACTPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	if (CameraManager)
	{
		CameraManager->AsyncCameraFade(1.0f, [this]() { TeleportToEndFloor(); });
	}

	EndLadder->SetInteractLockState(true);

	//SkyBikePawn->DestroyFireEffects();
}

void ASkyBikeGame::InteractSkyBike()
{
	SpawnAndPosessSkyBikePawn();
}

void ASkyBikeGame::TeleportToStartFloor()
{
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->TeleportTo(StartTeleportFloor->GetComponentLocation() + FVector(0.0f, 0.0f, 50.0f), StartTeleportFloor->GetComponentRotation());
}

void ASkyBikeGame::TeleportToEndFloor()
{
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->TeleportTo(EndTeleportFloor->GetComponentLocation() + FVector(0.0f, 0.0f, 50.0f), EndTeleportFloor->GetComponentRotation());
}

void ASkyBikeGame::SpawnAndPosessSkyBikePawn()
{
	PlayerController->SetActiveCTPlayer(false);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FRotator Rotator = SkyBike->GetComponentRotation();
	FVector SpawnLocation = SkyBike->GetComponentLocation() - FVector(0.0f,0.0f,10.0f);

	SkyBikePawn = (ASkyBikePawn*)GetWorld()->SpawnActor<ASkyBikePawn>(SkyBikePawnClass, SpawnLocation, Rotator, SpawnParams);
	SkyBikePawn->Init(SkyBikeStartPosition->GetComponentLocation(), SkyBikeEndPosition->GetComponentLocation(), this);

	PlayerController->Possess(SkyBikePawn);

	SkyBike->SetInteractLockState(true);
	SkyBike->SetVisibility(false);
}

void ASkyBikeGame::FailSkyBikeGame()
{
	EnableInput(PlayerController);
	PlayerController->PlayerCameraManager->StartCameraFade(0.0f, 3.0f, 3.0f, FLinearColor::Black, false, true);
	SkyBike->SetVisibility(true);
	SkyBike->SetInteractLockState(false);

	PlayerController->PossessedDefaultPawn();
	SkyBikePawn->Destroy();
}

