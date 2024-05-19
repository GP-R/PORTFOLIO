#include "ThrowBallGame/ThrowBallGame.h"
#include "ThrowBallGame/ThrowBallGameWidget.h"
#include "InteractiveMeshComponent.h"
#include "CTPlayerCharacter.h"
#include "CTPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

AThrowBallGame::AThrowBallGame()
{
	PrimaryActorTick.bCanEverTick = true;

	GameMachine = CreateDefaultSubobject<UInteractiveMeshComponent>(TEXT("GameMachine"));
	SetRootComponent(GameMachine);

	StartTransfrom = CreateDefaultSubobject<USceneComponent>(TEXT("Start Position"));
	StartTransfrom->SetupAttachment(GameMachine);

	static ConstructorHelpers::FClassFinder<UThrowBallGameWidget> GameWidgetBP(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_ThrowBallGame.WBP_ThrowBallGame_C'"));
	if (GameWidgetBP.Succeeded())
	{
		GameWidgetSubClass = GameWidgetBP.Class;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage(TEXT("AnimMontage'/Game/Blueprints/Character/Animation/ThrowBall/AM_ThrowBall.AM_ThrowBall'"));
	if (AnimMontage.Succeeded())
	{
		ThrowBallAnim = AnimMontage.Object;
	}
}

void AThrowBallGame::BeginPlay()
{
	Super::BeginPlay();
	
	FScriptDelegate StartThrowBallGameEvent;
	StartThrowBallGameEvent.BindUFunction(this, "InteractMachine");
	GameMachine->OnInteract.Add(StartThrowBallGameEvent);
	GameMachine->SetInteractLockState(false);

	if (GameWidgetSubClass != nullptr)
	{
		GameWidget = Cast<UThrowBallGameWidget>(CreateWidget(GetWorld(), GameWidgetSubClass));
		if (GameWidget != nullptr)
		{
			GameWidget->Init(this);
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AThrowBallGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanThrow)
	{
		if (ThrowPower >= 100.0f)
		{
			ThrowPowerChangeRate = -1.0f;
		}
		else if (ThrowPower < 0.0f)
		{
			ThrowPowerChangeRate = 1.0f;
		}
		ThrowPower += ThrowPowerChangeRate;
	}
}

void AThrowBallGame::InteractMachine()
{
	ACTPlayerCharacter* CTPlayer = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (CTPlayer == nullptr)
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
	// 캐릭터 위치 및 카메라 위치 변경
	CTPlayer->SetActorLocation(StartTransfrom->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);
	UCameraComponent* TempCamera = CTPlayer->GetPlayerCamera();
	FVector NewLocation = TempCamera->GetComponentLocation() - (CTPlayer->GetActorForwardVector() * 120);
	NewLocation += CTPlayer->GetActorRightVector() * 50.0f;
	NewLocation.Z += 40.0f;
	TempCamera->SetWorldLocation(NewLocation);
	
	// 카메라 고정
	FRotator NewRotator(-2.8f, GetActorRotation().Yaw, 0.0f);
	CTPlayerController->SetControlRotation(NewRotator);
	CTPlayerController->SetShowMouseCursor(true);

	// 캐릭터 설정
	CTPlayer->SetLockMoving(true);
	CTPlayer->SetLockRotation(true);
	CTPlayer->SetPlayerWidgetVisibility(false);

	FScriptDelegate SetThrowPowerEvent;
	SetThrowPowerEvent.BindUFunction(this, "SetThrowPower");
	CTPlayer->LeftMouseButtonClickEvent.Add(SetThrowPowerEvent);

	FScriptDelegate ThrowBallEvent;
	ThrowBallEvent.BindUFunction(this, "ThrowBall");
	CTPlayer->LeftMouseButtonClickReleasedEvent.Add(ThrowBallEvent);

	GameWidget->SetVisibility(ESlateVisibility::Visible);
	GameMachine->SetInteractLockState(true);
}

void AThrowBallGame::SetThrowPower()
{
	bCanThrow = true;
}

void AThrowBallGame::ThrowBall()
{
	bCanThrow = false;
	ACTPlayerCharacter* CTPlayer = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (CTPlayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTPlayerCharacter Casting Error [Class : MoleGame]"));
		return;
	}
	CTPlayer->PlayAnimMontage(ThrowBallAnim);
	ThrowPower = 0.0f;
	ThrowPowerChangeRate = 1.0f;
}