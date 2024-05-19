#include "MoleGame/Mole.h"
#include "MoleGame/Hammer.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UMole::UMole()
{
	bIsRising = false;
	bIsRedMole = false;
	MoveSpeed = 20.0f;
	StopTime = 0.5f;

	RedMoleMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Art/Mesh/M_RedMole.M_RedMole'"));
	CatchMoleEffect = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/VFX_JM/Particle/P_moleDam.P_moleDam'"));
}

void UMole::BeginPlay()
{
	Super::BeginPlay();

	SetInteractLockState(true);

	MoleInteractDelegate.BindUFunction(this, "InteractMole");
	OnInteract.Add(MoleInteractDelegate);

	OriginalPosition = GetComponentLocation();

	OriginalMaterial = GetMaterial(0);
}

void UMole::Init(AMoleGame* NewMoleGame)
{
	if (NewMoleGame != nullptr)
	{
		MoleGame = NewMoleGame;
	}
}

bool UMole::RiseAndFall()
{
	if (bIsRising)
	{
		return false;
	}
	bIsRising = true;
	SetInteractLockState(false);

	GetWorld()->GetTimerManager().SetTimer(RiseTimer, this, &UMole::Rise, 0.01f, true);
	return true;
}

void UMole::Rise()
{
	FVector TargetLocation = OriginalPosition + FVector(0.0f, 0.0f, 10.0f);
	FVector NewLocation = FMath::VInterpTo(GetComponentLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), MoveSpeed);
	SetWorldLocation(NewLocation);

	if (FVector::DistSquared(GetComponentLocation(), TargetLocation) < KINDA_SMALL_NUMBER)
	{
		GetWorld()->GetTimerManager().SetTimer(FallTimer, this, &UMole::Fall, 0.01f, true, StopTime);
		GetWorld()->GetTimerManager().ClearTimer(RiseTimer);
	}
}

void UMole::Fall()
{
	FVector NewLocation = FMath::VInterpTo(GetComponentLocation(), OriginalPosition, GetWorld()->GetDeltaSeconds(), MoveSpeed);
	SetWorldLocation(NewLocation);
	if (FVector::DistSquared(GetComponentLocation(), OriginalPosition) < KINDA_SMALL_NUMBER)
	{
		GetWorld()->GetTimerManager().ClearTimer(FallTimer);
		bIsRising = false;
		SetInteractLockState(true);
		if (bIsRedMole)
		{
			ChangeMoleState(false);
		}
	}
}

bool UMole::ChangeMoleState(bool bRedMole)
{
	if (bIsRising)
	{
		return false;
	}

	if (bRedMole && RedMoleMaterial != nullptr)
	{
		bIsRedMole = true;
		if (IsValid(RedMoleMaterial))
		{
			SetMaterial(0, RedMoleMaterial);
		}
	}
	else
	{
		bIsRedMole = false;
		if (IsValid(OriginalMaterial))
		{
			SetMaterial(0, OriginalMaterial);
		}
	}

	return true;
}


void UMole::InteractMole()
{
	if (GetInteractLockState())
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(RiseTimer);
	GetWorld()->GetTimerManager().ClearTimer(FallTimer);
	SetWorldLocation(OriginalPosition);
	bIsRising = false;
	SetInteractLockState(true);

	if (Hammer)
	{
		FVector Location = OriginalPosition + FVector(0.0f, 0.0f, 20.0f) + MoleGame->GetActorForwardVector() * -20.0f;
		FRotator Rotation = MoleGame->GetMoleMachine()->GetRelativeRotation() + FRotator(0.0f, 90.0f, 0.0f);
		FActorSpawnParameters SpawnParameters;
		AHammer* SpawnedHammer = GetWorld()->SpawnActor<AHammer>(Hammer, Location, Rotation, SpawnParameters);
		if (SpawnedHammer)
		{
			SpawnedHammer->Init(MoleGame);
			SpawnedHammer->Hit();
		}
	}

	if (bIsRedMole)
	{
		ChangeMoleState(false);
		FVector BloodEffectSpawnLocation = GetComponentLocation() + FVector(0.0f, 0.0f, 5.0f);
		FRotator BloodEffectSpawnRotation = FRotator::ZeroRotator;
		if (CatchRedMoleEffect)
		{
			//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ParticleEffect, BloodEffectSpawnLocation, BloodEffectSpawnRotation);
		}

		MoleGame->MoleGameFailEvent.Broadcast();
	}
	else
	{
		FVector CatchEffectSpawnLocation = GetComponentLocation() + FVector(0.0f, 0.0f, 5.0f);
		FRotator CatchEffectSpawnRotation = FRotator::ZeroRotator;
		if (CatchMoleEffect)
		{
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CatchMoleEffect, CatchEffectSpawnLocation, CatchEffectSpawnRotation);
		}

		MoleGame->CatchMoleEvent.Broadcast();
	}
}

void UMole::Clear()
{
	GetWorld()->GetTimerManager().ClearTimer(RiseTimer);
	GetWorld()->GetTimerManager().ClearTimer(FallTimer);
	bIsRising = false;
	SetInteractLockState(true);
	SetWorldLocation(OriginalPosition);
	ChangeMoleState(false);
}