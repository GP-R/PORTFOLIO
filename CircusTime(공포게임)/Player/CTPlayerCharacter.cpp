#include "CTPlayerCharacter.h"
#include "CTPlayerWidget.h"
#include "CTPlayerController.h"
#include "InteractiveMeshComponent.h"
#include "PlayerFootstepData.h"
#include "InteractionObject/ObjectZoomComponent.h"
#include "InteractionObject/ExploreWidget.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "MatineeCameraShake.h"
#include "Sound/SoundBase.h"
#include "Components/SpotLightComponent.h"

// Debug Header
#include "DrawDebugHelpers.h"

ACTPlayerCharacter::ACTPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetRelativeLocation(FVector(30.0f, 0.0f, 70.0f));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm);

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
	FlashLight->IntensityUnits = ELightUnits::Lumens;
	FlashLight->Intensity = 250.0f;
	FlashLight->AttenuationRadius = 6000.0f;
	FlashLight->SetupAttachment(Camera);

	PlayerWidget = CreateDefaultSubobject<UCTPlayerWidget>(TEXT("PlayerWidget"));
	ExploreWidget = CreateDefaultSubobject<UExploreWidget>(TEXT("ExploreWidget"));

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCapsuleComponent()->bReturnMaterialOnMove = true;

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UCTPlayerWidget> PlayerWidgetBP(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_CTPlayerWidget.WBP_CTPlayerWidget_C'"));
	if (PlayerWidgetBP.Succeeded())
	{
		PlayerWidgetAsset = PlayerWidgetBP.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UExploreWidget> ExploreWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_Explore.WBP_Explore_C'"));
	if (ExploreWidgetClass.Succeeded())
	{
		ExploreWidgetBP = ExploreWidgetClass.Class;
	}
}

void ACTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Movement.WalkSpeed;

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (CameraManager)
	{
		CameraManager->ViewPitchMin = CameraSetting.MinPitch;
		CameraManager->ViewPitchMax = CameraSetting.MaxPitch;
	}

	LastLocation = GetActorLocation();
	LastFootstepLocation = GetActorLocation();
	TravelDistance = 0.0f;

	if (PlayerWidgetAsset != nullptr)
	{
		PlayerWidget = Cast<UCTPlayerWidget>(CreateWidget(GetWorld(), PlayerWidgetAsset));
		if (PlayerWidget != nullptr)
		{
			PlayerWidget->AddToViewport();
			PlayerWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (ExploreWidgetBP != nullptr)
	{
		ExploreWidget = Cast<UExploreWidget>(CreateWidget(GetWorld(), ExploreWidgetBP));
		if (ExploreWidget != nullptr)
		{
			ExploreWidget->AddToViewport();
			ExploreWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ACTPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAim();
	UpdateCameraShake();
}

void ACTPlayerCharacter::DisablePlayerInput(bool bActiveWidget)
{
	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!bActiveWidget)
	{
		PlayerWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ACTPlayerCharacter::EnablePlayerInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		PlayerWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

UCTPlayerWidget* ACTPlayerCharacter::GetPlayerWidget()
{
	return PlayerWidget;
}

void ACTPlayerCharacter::UpdateAim()
{
	FVector OutWorldLocation;
	FVector OutWorldDirection;
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FColor DrawColor;

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ScreenAimPos = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
	if (PlayerController != nullptr)
	{
		if (PlayerController->bShowMouseCursor == true)
		{
			PlayerController->GetMousePosition(ScreenAimPos.X, ScreenAimPos.Y);
		}
	}

	bool bAim = UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(ScreenAimPos.X, ScreenAimPos.Y, OutWorldLocation, OutWorldDirection);
	if (!bAim)
	{
		return;
	}

	bool bHitResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		OutWorldLocation,
		(OutWorldDirection * InteractionRange) + OutWorldLocation,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params);

	/*DrawDebugLine(
		GetWorld(),
		OutWorldLocation,
		(OutWorldDirection * InteractionRange) + OutWorldLocation,
		FColor::Red,    // 라인의 색상
		false,          // 영구적인 라인이 아님
		5.0f,           // 5초 동안 보여줌
		0,              // 깊이 우선순위는 기본값
		0.1f            // 라인의 두께
	);*/

	if (bHitResult)
	{

		InteractionObject = Cast<UInteractiveMeshComponent>(HitResult.Component);
		if (InteractionObject && !InteractionObject->GetInteractLockState())
		{
			InteractionObject->OnHighLight.Broadcast();
			PlayerWidget->SetVisibleInteractText(true);
		}
		else
		{
			PlayerWidget->SetVisibleInteractText(false);
		}
	}
	else
	{
		if (InteractionObject != nullptr)
		{
			InteractionObject->OnEndHighLight.Broadcast();
			InteractionObject = nullptr;
			PlayerWidget->SetVisibleInteractText(false);
		}
	}

	FHitResult LightCheck;
	bHitResult = GetWorld()->LineTraceSingleByChannel(
		LightCheck,
		OutWorldLocation,
		(OutWorldDirection * 1000) + OutWorldLocation,
		ECC_Visibility);

	/*if (bHitResult)
	{
		float Distance = FVector::Dist(GetActorLocation(), LightCheck.Location);
		UE_LOG(LogTemp, Log, TEXT("%f"), Distance);

		float NewIntensity;
		if (Distance < 300.0f)
		{
			NewIntensity = 50.0f;
		}
		else if (Distance > 500.0f)
		{
			NewIntensity = 320.0f;
		}
		else
		{
			NewIntensity = 250.0f;
		}
		FlashLight->Intensity = NewIntensity;
		FlashLight->SetVisibility(false);
		FlashLight->SetVisibility(true);
	}
	else
	{
		FlashLight->Intensity = 250.0f;
	}*/
}

void ACTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ACTPlayerCharacter::Interaction);
	PlayerInputComponent->BindAction(TEXT("LeftMouseButtonClick"), IE_Pressed, this, &ACTPlayerCharacter::LeftMouseButtonClick);
	PlayerInputComponent->BindAction(TEXT("LeftMouseButtonClick"), IE_Repeat, this, &ACTPlayerCharacter::LeftMouseButtonClickRepeat);
	PlayerInputComponent->BindAction(TEXT("LeftMouseButtonClick"), IE_Released, this, &ACTPlayerCharacter::LeftMouseButtonClickReleased);
	
	PlayerInputComponent->BindAction(TEXT("ObjectZoom"), IE_Pressed, this, &ACTPlayerCharacter::WheelButtonClick);
	PlayerInputComponent->BindAction(TEXT("ObjectZoom"), IE_Released, this, &ACTPlayerCharacter::WheelButtonReleased);

	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ACTPlayerCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &ACTPlayerCharacter::StopRunning);
	PlayerInputComponent->BindAction(TEXT("OnFlashLight"), IE_Pressed, this, &ACTPlayerCharacter::TurnOnFlashLight);
	PlayerInputComponent->BindAction(TEXT("Cancel"), IE_Pressed, this, &ACTPlayerCharacter::Cancel);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACTPlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACTPlayerCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACTPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACTPlayerCharacter::LookUp);
}

void ACTPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<ACTPlayerController>(NewController);

	if (PlayerController)
	{
		PlayerController->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 1.0f, FLinearColor::Black, false, true);

		/*if (PlayerWidgetAsset != nullptr)
		{
			PlayerWidget = Cast<UCTPlayerWidget>(CreateWidget(GetWorld(), PlayerWidgetAsset));
			if (PlayerWidget != nullptr)
			{
				PlayerWidget->AddToViewport();
			}
		}*/

		EnablePlayerInput();
	}
}

void ACTPlayerCharacter::UnPossessed()
{
	Super::UnPossessed();

	PlayerWidget->SetVisibility(ESlateVisibility::Hidden);
	
}

void ACTPlayerCharacter::PlayFootstepSound()
{
	GetCharacterMovement()->FindFloor(GetCapsuleComponent()->GetComponentLocation(), FloorResult, false);

	if (FloorResult.bBlockingHit)
	{
		if (IsValid(GetFootstepSound(&FloorResult.HitResult.PhysMaterial)))
		{
			UGameplayStatics::PlaySoundAtLocation(this, GetFootstepSound(&FloorResult.HitResult.PhysMaterial), FloorResult.HitResult.Location);
		}
	}

	LastFootstepLocation = FloorResult.HitResult.Location;
}

USoundBase* ACTPlayerCharacter::GetFootstepSound(TWeakObjectPtr<UPhysicalMaterial>* Surface)
{
	for (auto FootstepMapping : FootstepSettings.Mappings)
	{
		if (FootstepMapping && FootstepMapping->GetPhysicalMaterial() == Surface->Get())
		{
			CurrentFootstepMapping = FootstepMapping;
			FootstepSettings.CurrentStride = bIsRunning ? FootstepMapping->GetFootstepStride_Run() : FootstepMapping->GetFootstepStride_Walk();
			return FootstepMapping->GetFootstepSounds()[FMath::RandRange(0, FootstepMapping->GetFootstepSounds().Num() - 1)];
		}
	}

	return nullptr;
}

void ACTPlayerCharacter::UpdateCameraShake()
{

	/*if (GetVelocity().Size() > 0)
	{
		PlayerController->ClientStartCameraShake(CameraShakes.WalkShake, 2.0f);
	}
	else
	{
		PlayerController->ClientStartCameraShake(CameraShakes.IdleShake, 1.0f);
	}

	if (GetVelocity().Size() > 0 && GetCharacterMovement()->MaxWalkSpeed >= Movement.RunSpeed && CanJump())
	{
		PlayerController->ClientStartCameraShake(CameraShakes.RunShake, 1.0f);
	}*/
}

void ACTPlayerCharacter::UpDown(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	if (bLockMoving)
	{
		return;
	}

	AddMovementInput(GetActorForwardVector(), Value);

	if (FootstepSettings.bEnableFootsteps)
	{
		if (GetCharacterMovement()->Velocity.Size() > 0.0f && GetCharacterMovement()->IsMovingOnGround())
		{
			TravelDistance += (GetActorLocation() - LastLocation).Size();
			LastLocation = GetActorLocation();
		}

		if (GetCharacterMovement()->IsMovingOnGround() && TravelDistance > FootstepSettings.CurrentStride)
		{
			PlayFootstepSound();
			TravelDistance = 0;
		}
	}
}

void ACTPlayerCharacter::LeftRight(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	if (bLockMoving)
	{
		return;
	}

	AddMovementInput(GetActorRightVector(), Value);
}

void ACTPlayerCharacter::Turn(float Value)
{
	if (bZoomMode)
	{
		if (bWheelButtonDown && ZoomObject != nullptr)
		{
			FRotator NewRotation;
			NewRotation.Yaw = (-1.0f * Value) * ZoomObjectRotationSpeed ;
			FQuat QuatRotation = FQuat(NewRotation);
			//ZoomObject->GetOwner()->AddActorWorldRotation(QuatRotation);
			ZoomObject->AddRelativeRotation(QuatRotation);
		}
	}
	if (bLockRotation)
	{
		return;
	}
	AddControllerYawInput(Value);
}

void ACTPlayerCharacter::LookUp(float Value)
{
	if (bZoomMode)
	{
		if (bWheelButtonDown && ZoomObject != nullptr)
		{
			FRotator NewRotation;
			NewRotation.Pitch = Value * ZoomObjectRotationSpeed;
			FQuat QuatRotation = FQuat(NewRotation);
			//ZoomObject->GetOwner()->AddActorWorldRotation(QuatRotation);
			ZoomObject->AddRelativeRotation(QuatRotation);
			
		}
	}
	if (bLockRotation)
	{
		return;
	}
	AddControllerPitchInput(Value);
}

void ACTPlayerCharacter::Interaction()
{
	UE_LOG(LogTemp, Log, TEXT("Interaction"));
	if (InteractionObject != nullptr && !InteractionObject->GetInteractLockState())
	{
		InteractionObject->OnInteract.Broadcast();
	}
}

void ACTPlayerCharacter::Run()
{
	if (FMath::IsNearlyEqual(GetVelocity().Size(), 0.0f, 0.0001f) || Stamina < 20.0f)
	{
		return;
	}

	if (GetWorld()->GetTimerManager().IsTimerActive(UnUseStaminaTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(UnUseStaminaTimerHandle);
	}

	GetCharacterMovement()->MaxWalkSpeed = Movement.RunSpeed;
	bIsRunning = true;

	GetWorld()->GetTimerManager().SetTimer(UseStaminaTimerHandle, [this]()
		{
			Stamina -= 1.0f;
			if (Stamina <= 0.0f)
			{
				Stamina = 0.0f;
				GetCharacterMovement()->MaxWalkSpeed = Movement.WalkSpeed;
				GetWorld()->GetTimerManager().ClearTimer(UseStaminaTimerHandle);
			}
		}, 1.0f / 20.0f, true);
}

void ACTPlayerCharacter::StopRunning()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(UseStaminaTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(UseStaminaTimerHandle);
	}

	GetCharacterMovement()->MaxWalkSpeed = Movement.WalkSpeed;
	bIsRunning = false;

	TWeakObjectPtr<ACTPlayerCharacter> WeakThis(this);

	GetWorld()->GetTimerManager().SetTimer(UnUseStaminaTimerHandle, [WeakThis]()
		{
			if (!WeakThis.IsValid())
			{
				return;
			}
			ACTPlayerCharacter* StrongThis = WeakThis.Get();
			StrongThis->Stamina += 1.0f;
			if (StrongThis->Stamina >= 100.0f)
			{
				StrongThis->Stamina = 100.0f;
				if (StrongThis->GetWorld())
				{
					StrongThis->GetWorld()->GetTimerManager().ClearTimer(WeakThis->UnUseStaminaTimerHandle);
				}
				return;
			}
		}, 1.0f / 10.0f, true);
}

void ACTPlayerCharacter::TurnOnFlashLight()
{
	if (bHasFlashLight)
	{
		FlashLight->SetVisibility(!FlashLight->IsVisible());
		if (IsValid(OnFlashLightSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, OnFlashLightSound, GetActorLocation());
		}
	}
}

float ACTPlayerCharacter::GetStaminaValue()
{
	return Stamina;
}

void ACTPlayerCharacter::SetUseFlashLight(bool bCanUse)
{
	bHasFlashLight = bCanUse;
	if (!bCanUse)
	{
		FlashLight->SetVisibility(false);
	}
}

void ACTPlayerCharacter::OnInteraction(bool bActiveUI)
{
	PlayerWidget->SetVisibleInteractText(bActiveUI);
}

void ACTPlayerCharacter::SetPlayerWidgetVisibility(bool bVisible)
{
	if (bVisible)
	{
		PlayerWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PlayerWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ACTPlayerCharacter::LeftMouseButtonClick()
{
	bLeftButtonDown = true;
	LeftMouseButtonClickEvent.Broadcast();
}

void ACTPlayerCharacter::LeftMouseButtonClickRepeat()
{
	UE_LOG(LogTemp, Log, TEXT("Repeat"));
	LeftMouseButtonClickRepeatEvent.Broadcast();
}

void ACTPlayerCharacter::LeftMouseButtonClickReleased()
{
	UE_LOG(LogTemp, Log, TEXT("Released"));
	LeftMouseButtonClickReleasedEvent.Broadcast();
	bLeftButtonDown = false;
}

void ACTPlayerCharacter::WheelButtonClick()
{
	bWheelButtonDown = true;
}

void ACTPlayerCharacter::WheelButtonReleased()
{
	bWheelButtonDown = false;
}

void ACTPlayerCharacter::Cancel()
{
	if (bZoomMode == true && ZoomObject != nullptr)
	{
		ExploreWidget->SetVisibility(ESlateVisibility::Hidden);
		ZoomObject->ReturnObject();
	}
}

void ACTPlayerCharacter::Explore(UObjectZoomComponent* NewExploreObject)
{
	ZoomObject = NewExploreObject;
	ExploreWidget->SetExploreWidget(ZoomObject->GetInfo().Name, ZoomObject->GetInfo().Description);
	ExploreWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACTPlayerCharacter::SetZoomMode(bool bValue)
{
	bZoomMode = bValue;
	if (bZoomMode)
	{
		SetLockMoving(true);
		SetLockRotation(true);
	}
	else
	{
		SetLockMoving(false);
		SetLockRotation(false);
	}
}