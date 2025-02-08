#include "FindMaskGame/SelectMaskWidget.h"
#include "FindMaskGame/SelectMaskPawn.h"
#include "FindMaskGame/MaskGameBodyActor.h"
#include "FindMaskGame/MaskGameMaskActor.h"
#include "CTPlayerController.h"
#include "CTGameMode.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateBrush.h"

void USelectMaskWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LeftSelectBodyButton = Cast<UButton>(GetWidgetFromName(TEXT("LeftSelectBodyButton")));
	RightSelectBodyButton = Cast<UButton>(GetWidgetFromName(TEXT("RightSelectBodyButton")));
	LeftSelectMaskButton = Cast<UButton>(GetWidgetFromName(TEXT("LeftSelectMaskButton")));
	RightSelectMaskButton = Cast<UButton>(GetWidgetFromName(TEXT("RightSelectMaskButton")));
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));

	LeftSelectBodyButton->OnClicked.AddDynamic(this, &USelectMaskWidget::OnLeftSelectBodyButtonClicked);
	RightSelectBodyButton->OnClicked.AddDynamic(this, &USelectMaskWidget::OnRightSelectBodyButtonClicked);
	LeftSelectMaskButton->OnClicked.AddDynamic(this, &USelectMaskWidget::OnLeftSelectMaskButtonClicked);
	RightSelectMaskButton->OnClicked.AddDynamic(this, &USelectMaskWidget::OnRightSelectMaskButtonClicked);
	ExitButton->OnClicked.AddDynamic(this, &USelectMaskWidget::OnExitButtonClicked);

	CurVisibleImageIndex = 0;
	bCameraMoving = false;
}

void USelectMaskWidget::OnLeftSelectBodyButtonClicked()
{

	ASelectMaskPawn* MaskPawn = Cast<ASelectMaskPawn>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MaskPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}

	if (MaskPawn->GetCurrentSelectedBody() != nullptr)
	{
		CameraMove(MaskPawn, MaskPawn->GetCurrentSelectedBody()->PrevBodyActor, 1.0f);
	}
	

}

void USelectMaskWidget::OnRightSelectBodyButtonClicked()
{
	ASelectMaskPawn* MaskPawn = Cast<ASelectMaskPawn>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MaskPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}

	if (MaskPawn->GetCurrentSelectedBody() != nullptr)
	{
		CameraMove(MaskPawn, MaskPawn->GetCurrentSelectedBody()->NextBodyActor, 1.0f);
	}

}

void USelectMaskWidget::OnLeftSelectMaskButtonClicked()
{
	if (MaskImageArray.Num() == 0)
	{
		return;
	}
	CurVisibleImageIndex -= 1;
	if (CurVisibleImageIndex < 0)
	{
		CurVisibleImageIndex = MaskImageArray.Num() - 1;
	}
	ChangeMaskImage(CurVisibleImageIndex);
}

void USelectMaskWidget::OnRightSelectMaskButtonClicked()
{
	if (MaskImageArray.Num() == 0)
	{
		return;
	}
	CurVisibleImageIndex += 1;
	if (CurVisibleImageIndex >= MaskImageArray.Num())
	{
		CurVisibleImageIndex = 0;
	}
	ChangeMaskImage(CurVisibleImageIndex);
}

void USelectMaskWidget::ChangeMaskImage(int32 Index)
{
	FSlateBrush Brush;
	if (MaskImageArray.Num() == 0)
	{
		Brush.SetResourceObject(EmptyMaskImage);
		MaskImage->SetBrush(Brush);
		return;
	}
	Brush.SetResourceObject(MaskImageArray[Index]);
	MaskImage->SetBrush(Brush);
}

void USelectMaskWidget::Successed()
{
	UE_LOG(LogTemp, Warning, TEXT("Success!"));
	SuccessText->SetOpacity(1.0f);
	PlayEndMaskGameCinematic();
	GetWorld()->GetTimerManager().SetTimer(ExitGame, this, &USelectMaskWidget::OnExitButtonClicked, 3.0f, false);
}

void USelectMaskWidget::OnExitButtonClicked()
{
	ACTPlayerController* CTPlayerController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CTPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting Error"));
		return;
	}
	CTPlayerController->PossessedDefaultPawn();
	FInputModeGameOnly GameOnlyInputMode;
	CTPlayerController->SetInputMode(GameOnlyInputMode);
	CurVisibleImageIndex = 0;
}

void USelectMaskWidget::CameraMove(AActor* ActorToMove, AMaskGameBodyActor* Target, float Duration)
{
	if (!ActorToMove) return;

	if (ActorToMove->GetWorldTimerManager().IsTimerActive(MoveTimerHandle))
	{
		return;
	}


	float ElapsedTime = 0.0f;

	TimerDel.BindLambda([ActorToMove, Target, Duration, ElapsedTime]() mutable
		{
			ElapsedTime += ActorToMove->GetWorld()->DeltaTimeSeconds;
			float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f);
			
			FVector NewLocation = FMath::Lerp(ActorToMove->GetActorLocation(), Target->BodyCameraPosition->GetComponentLocation(), Alpha);

			FQuat NewRotation = FQuat::Slerp(ActorToMove->GetActorQuat(), Target->BodyCameraPosition->GetComponentQuat(), Alpha);

			ActorToMove->SetActorLocationAndRotation(NewLocation, NewRotation.Rotator());

			if (Alpha >= 1.0f)
			{
				ASelectMaskPawn* Pawn = Cast<ASelectMaskPawn>(ActorToMove);
				Pawn->SetCurrentSelectedBody(Target);
				ActorToMove->GetWorldTimerManager().ClearTimer(Pawn->GetMaskGameWidget()->MoveTimerHandle);
			}

		});

	ActorToMove->GetWorldTimerManager().SetTimer(MoveTimerHandle, TimerDel, 0.01f, true);
}

TArray<UTexture2D*> USelectMaskWidget::GetMaskImageArray()
{
	return MaskImageArray;
}

void USelectMaskWidget::AddMaskImage(UTexture2D* Image)
{
	MaskImageArray.Add(Image);
}

void USelectMaskWidget::RemoveMaskImage(UTexture2D* Image)
{
	MaskImageArray.Remove(Image);
	CurVisibleImageIndex += 1;
	if (CurVisibleImageIndex >= MaskImageArray.Num())
	{
		CurVisibleImageIndex = 0;
	}
	ChangeMaskImage(CurVisibleImageIndex);
}