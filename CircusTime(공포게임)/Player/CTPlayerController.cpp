// Fill out your copyright notice in the Description page of Project Settings.


#include "CTPlayerController.h"
#include "CTPlayerCharacter.h"
#include "CTPlayerWidget.h"
#include "CTGameMode.h"
#include "Dialogue/DialogueController.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ACTPlayerController::ACTPlayerController()
{
	DialogueController = CreateDefaultSubobject<UDialogueController>(TEXT("DialogueController"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	PauseMenuWidget = CreateDefaultSubobject<UUserWidget>(TEXT("PauseMenuWidget"));

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuWidgetRef(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_PauseMenu.WBP_PauseMenu_C'"));
	if (PauseMenuWidgetRef.Succeeded())
	{
		PauseMenuWidgetClass = PauseMenuWidgetRef.Class;
	}
}

void ACTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	DialogueController->Init();

	if (PauseMenuWidgetClass != nullptr)
	{
		PauseMenuWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), PauseMenuWidgetClass));
		if (PauseMenuWidget != nullptr)
		{
			PauseMenuWidget->AddToViewport();
			PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ACTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("NextDialogue", IE_Pressed, this, &ACTPlayerController::NextDialogue);
	InputComponent->BindAction("Exit", IE_Pressed, this, &ACTPlayerController::TogglePauseMenuWidget);
}

void ACTPlayerController::NextDialogue()
{
	//DialogueController->PrintDialogue();
}

void ACTPlayerController::TogglePauseMenuWidget()
{
	UWorld* WorldRef = GetWorld();
	if (WorldRef == nullptr)
	{
		return;
	}

	bool bPaused = UGameplayStatics::IsGamePaused(GetWorld());
	if (bPaused)
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		SetShowMouseCursor(false);

		UGameplayStatics::SetGamePaused(WorldRef, false);
	}
	else
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);

		FInputModeUIOnly InputMode;
		SetInputMode(InputMode);
		SetShowMouseCursor(true);

		UGameplayStatics::SetGamePaused(WorldRef, true);
	}
	
}

void ACTPlayerController::SetActiveCTPlayer(bool bIsActive)
{

	ACTGameMode* CTGameMode = Cast<ACTGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CTGameMode == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}

	ACTPlayerCharacter* CTPlayer = Cast<ACTPlayerCharacter>(CTGameMode->DefaultPawnInstance);
	if (CTPlayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}
	
	if (bIsActive)
	{
		CTPlayer->GetPlayerWidget()->SetVisibility(ESlateVisibility::Visible);
		CTPlayer->SetActorHiddenInGame(false);
		CTPlayer->SetActorEnableCollision(true);
		CTPlayer->SetActorTickEnabled(true);
		
	}
	else
	{
		CTPlayer->GetPlayerWidget()->SetVisibility(ESlateVisibility::Hidden);
		CTPlayer->SetActorHiddenInGame(true);
		CTPlayer->SetActorEnableCollision(false);
		CTPlayer->SetActorTickEnabled(false);
	}
}

void ACTPlayerController::PossessedDefaultPawn()
{
	SetActiveCTPlayer(true);

	ACTGameMode* CTGameMode = Cast<ACTGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CTGameMode == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(CTGameMode->DefaultPawnInstance);
}
