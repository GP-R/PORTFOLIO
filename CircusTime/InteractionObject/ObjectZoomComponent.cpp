#include "InteractionObject/ObjectZoomComponent.h"

#include "CTPlayerCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Engine/PostProcessVolume.h"

UObjectZoomComponent::UObjectZoomComponent()
{
	FScriptDelegate InteractedDelegate;
	InteractedDelegate.BindUFunction(this, "InteractZoomObject");
	OnInteract.Add(InteractedDelegate);
}

void UObjectZoomComponent::InteractZoomObject()
{
	OriginalTransform = GetComponentTransform();
	ACTPlayerCharacter* RefPlayer = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (RefPlayer)
	{
		if (BlurVolume == nullptr || !IsValid(BlurVolume))
		{
			CreatePostProcessVolume();
		}
		BlurVolume->bEnabled = true;

		RefPlayer->SetUseFlashLight(false);
		RefPlayer->Explore(this);
		RefPlayer->SetPlayerWidgetVisibility(false);
		FVector NewLocation = RefPlayer->GetPlayerCamera()->GetComponentLocation();
		NewLocation += RefPlayer->GetPlayerCamera()->GetForwardVector() * DistanceInFrontOfPlayer;
		NewLocation += (RefPlayer->GetPlayerCamera()->GetRightVector() * -1.0f) * 10.0f;
		SetWorldLocation(NewLocation);
		//GetOwner()->SetActorLocation(NewLocation);

		FVector PlayerForwardVector = RefPlayer->GetPlayerCamera()->GetForwardVector();
		FVector NewTargetLocation = GetComponentLocation() + PlayerForwardVector;
		FRotator NewRotation = FRotationMatrix::MakeFromX(NewTargetLocation - GetComponentLocation()).Rotator();
		SetWorldRotation(NewRotation);
		//GetOwner()->SetActorRotation(NewRotation);

		RefPlayer->SetZoomMode(true);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);

		FInputModeGameAndUI InputMode;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputMode);
	}

	SetInteractLockState(true);
}

void UObjectZoomComponent::ReturnObject()
{
	SetWorldTransform(OriginalTransform);
	ACTPlayerCharacter* RefPlayer = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (RefPlayer)
	{
		RefPlayer->ZoomObject = nullptr;
		RefPlayer->SetZoomMode(false);
		RefPlayer->SetPlayerWidgetVisibility(true);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);

		FInputModeGameOnly InputMode;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputMode);
	}
	SetInteractLockState(false);
	BlurVolume->bEnabled = false;
	RefPlayer->SetUseFlashLight(true);
	//BlurVolume->Destroy();
}

bool UObjectZoomComponent::CreatePostProcessVolume()
{
	BlurVolume = GetWorld()->SpawnActor<APostProcessVolume>(APostProcessVolume::StaticClass());
	if (BlurVolume)
	{
		ACTPlayerCharacter* RefPlayer = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (RefPlayer)
		{
			FVector VolumeLocation = RefPlayer->GetActorLocation();
			//FVector VolumeExtent = FVector(2.f, 2.f, 2.f);

			BlurVolume->SetActorLocation(VolumeLocation);
			//BlurVolume->SetActorScale3D(VolumeExtent);
		}
		BlurVolume->bUnbound = true;
		BlurVolume->Settings.bOverride_DepthOfFieldFstop = true;
		BlurVolume->Settings.bOverride_DepthOfFieldFocalDistance = true;
		BlurVolume->Settings.DepthOfFieldFstop = 1.0f;
		BlurVolume->Settings.DepthOfFieldFocalDistance = 40.0f;
		
	}

	return true;
}