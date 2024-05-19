#include "SkyBikeGame/SkyBikePawn.h"
#include "SkyBikeGame/SkyBikeGame.h"
#include "CTPlayerController.h"
#include "CTGameMode.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ASkyBikePawn::ASkyBikePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BikeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BikeMesh"));
	BikeMesh->SetupAttachment(Root);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);
	SpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 100.0f));
	SpringArm->SetRelativeRotation(FRotator(-20.0f, 90.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);



}

void ASkyBikePawn::BeginPlay()
{
	Super::BeginPlay();
	
	float RandomTime = FMath::RandRange(0.5f, 1.5f);
	GetWorld()->GetTimerManager().SetTimer(ToggleTimerHandle, this, &ASkyBikePawn::ToggleDirection, RandomTime, false);

}

void ASkyBikePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AnimPitch > 35.0f)
	{
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		UAnimInstance* AnimInstance = BikeMesh->GetAnimInstance();
		if (AnimInstance)
		{
			if (!AnimInstance->IsAnyMontagePlaying() && LeftFallDown)
			{
				AnimInstance->Montage_Play(LeftFallDown);
			}
		}
		return;
	}
	else if (AnimPitch < -35.0f)
	{
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		UAnimInstance* AnimInstance = BikeMesh->GetAnimInstance();
		if (AnimInstance)
		{
			if (!AnimInstance->IsAnyMontagePlaying() && RightFallDown)
			{
				AnimInstance->Montage_Play(RightFallDown);
			}
		}
		return;
	}

	SetActorLocation(GetActorLocation() + (Direction * MoveSpeed * DeltaTime));

	// ÀÌÆåÆ® ½ºÆù
	TimeSinceLastSpawn += DeltaTime;
	if (TimeSinceLastSpawn >= SpawnInterval)
	{
		TimeSinceLastSpawn = 0.0f;

		FVector SpawnLocation = GetActorLocation() - (Direction * 50.0f) + FVector(0.0f, 0.0f, -3.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FVector EffectScale = FVector(0.5f, 0.5f, 0.5f);
		
		if (ParticleEffect)
		{
			UNiagaraComponent* FireEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ParticleEffect, SpawnLocation, SpawnRotation, EffectScale);
			if (FireEffect)
			{
				SpawnedEffects.Add(FireEffect);
			}
		}
	}

	float RotationAmount = RotationSpeed * DeltaTime;
	if (bRotateLeft)
	{
		AnimPitch -= RotationAmount;
	}
	else
	{
		AnimPitch += RotationAmount;
	}
	
	// TODO: Arrive
	FVector PawnToDest = Destination - GetActorLocation();
	float DotProduct = FVector::DotProduct(Direction, PawnToDest.GetSafeNormal());
	if (FMath::IsNearlyEqual(DotProduct, -1.f, 0.1f))
	{
		ACTPlayerController* CTController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CTController)
		{
			ACTGameMode* CTGameMode = Cast<ACTGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			if (CTGameMode == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
				return;
			}
			PlaySkyBikeCinematic();
			CTGameMode->DefaultPawnInstance->TeleportTo(SkyBikeGame->ClearGameTeleportLocation->GetComponentLocation(), SkyBikeGame->ClearGameTeleportLocation->GetComponentRotation());
			CTController->PossessedDefaultPawn();
			
			Destroy();
		}
	}
}

void ASkyBikePawn::ReSet()
{
	SkyBikeGame->FailSkyBikeGame();
	DestroyFireEffects();
}

void ASkyBikePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASkyBikePawn::RotatePitch);
}

void ASkyBikePawn::Init(FVector Source, FVector Dest, ASkyBikeGame* InSkyBikeGame)
{
	this->StartPosition = Source;
	this->Destination = Dest;

	FVector DirectionVector = Dest - Source;
	Direction = DirectionVector.GetSafeNormal();

	SkyBikeGame = InSkyBikeGame;
}

void ASkyBikePawn::MoveForward(float Value)
{
	if (Value == 0.f)
	{
		return;
	}
	
}

void ASkyBikePawn::RotatePitch(float Value)
{
	if (Value == 0.f)
	{
		return;
	}
	AnimPitch += -1.0f * Value;
}

void ASkyBikePawn::ToggleDirection()
{
	bRotateLeft = !bRotateLeft;

	float RandomTime = FMath::RandRange(0.5f, 1.5f);
	GetWorld()->GetTimerManager().SetTimer(ToggleTimerHandle, this, &ASkyBikePawn::ToggleDirection, RandomTime, false);
}

void ASkyBikePawn::DestroyFireEffects()
{
	for (UNiagaraComponent* Effect : SpawnedEffects)
	{
		if (Effect && Effect->IsValidLowLevel())
		{
			Effect->DestroyComponent();
		}
	}

	SpawnedEffects.Empty();
}