// Fill out your copyright notice in the Description page of Project Settings.


#include "MoleGame/MoleGame.h"
#include "MoleGame/Mole.h"
#include "InteractiveMeshComponent.h"

#include "CTPlayerCharacter.h"
#include "CTPlayerCameraManager.h"
#include "CTPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AMoleGame::AMoleGame()
{
	PrimaryActorTick.bCanEverTick = true;

	MoleMachine = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("MoleMachine"));
	SetRootComponent(MoleMachine);

	MoleArray.Reserve(MoleCount);
	for (int i = 0; i < MoleCount; ++i)
	{
		UMole* NewMole = CreateDefaultSubobject<UMole>(FName(TEXT("Mole"), i));
		MoleArray.Add(NewMole);
	}

	StartTransfrom = CreateDefaultSubobject<USceneComponent>(TEXT("Start Position"));
	StartTransfrom->SetupAttachment(MoleMachine);

	BloodWidget = CreateDefaultSubobject<UUserWidget>(TEXT("BloodWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> BloodWidgetBP(TEXT("WidgetBlueprint'/Game/VFX_JM/Particle_UI/PUI_Blood_2.PUI_Blood_2_C'"));
	if (BloodWidgetBP.Succeeded())
	{
		BloodWidgetClass = BloodWidgetBP.Class;
	}
}

void AMoleGame::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate MoleMachineDelegate;
	MoleMachineDelegate.BindUFunction(this, "InteractMoleMachine");
	MoleMachine->OnInteract.Add(MoleMachineDelegate);
	MoleMachine->SetInteractLockState(false);

	FScriptDelegate MoleGameFailDelegate;
	MoleGameFailDelegate.BindUFunction(this, "Fail");
	MoleGameFailEvent.Add(MoleGameFailDelegate);

	if (BloodWidgetClass)
	{
		BloodWidget = CreateWidget<UUserWidget>(GetWorld(), BloodWidgetClass);
		if (BloodWidget)
		{
			BloodWidget->AddToViewport();
			BloodWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	for (UMole* Mole : MoleArray)
	{
		Mole->Init(this);
	}
}

void AMoleGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastSpawn += DeltaTime;
}

void AMoleGame::InteractMoleMachine()
{
	Player = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTPlayerCharacter Casting Error [Class : MoleGame]"));
		return;
	}
	ACTPlayerController* CTPlayerController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CTPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTPlayerController Casting Error [Class : MoleGame]"));
		return;
	}
	Player->SetActorLocation(StartTransfrom->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);

	FRotator NewRotator(-39.0f, GetActorRotation().Yaw, 0.0f);
	CTPlayerController->SetControlRotation(NewRotator);
	CTPlayerController->SetShowMouseCursor(true);
	
	Player->SetLockMoving(true);
	Player->SetLockRotation(true);
	Player->SetPlayerWidgetVisibility(false);

	MoleMachine->SetInteractLockState(true);

	GetWorld()->GetTimerManager().SetTimer(MoleRiseTimer, this, &AMoleGame::RiseRandomMole, 0.5f, true);
	
	CatchMoleCount = 0;
}

void AMoleGame::RiseRandomMole()
{
	int32 RandomIndex = FMath::RandRange(0, MoleArray.Num() - 1);

	if (TimeSinceLastSpawn > RedMoleSpawnInterval)
	{
		if (IsValid(MoleArray[RandomIndex]))
		{
			if (!MoleArray[RandomIndex]->ChangeMoleState(true))
			{
				return;
			}
			TimeSinceLastSpawn = 0.0f;
		}
	}
	MoleArray[RandomIndex]->RiseAndFall();
}

void AMoleGame::Fail()
{
	MoleMachine->SetInteractLockState(false);
	GetWorld()->GetTimerManager().ClearTimer(MoleRiseTimer);
	Clear();

	ACTPlayerController* CTPlayerController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CTPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTPlayerController Casting Error [Class : MoleGame]"));
		return;
	}
	CTPlayerController->SetShowMouseCursor(false);
	Player->SetLockMoving(false);
	Player->SetLockRotation(false);

	ACTPlayerCameraManager* CameraManager = Cast<ACTPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	if (CameraManager)
	{
		CameraManager->AsyncCameraFade(1.0f, [this]()
			{
				if (BloodWidget)
				{
					BloodWidget->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		);
	}
	CatchMoleCount = 0;
}

void AMoleGame::Clear()
{
	for (UMole* Mole : MoleArray)
	{
		Mole->Clear();
	}
}