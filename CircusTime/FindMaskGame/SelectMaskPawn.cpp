#include "FindMaskGame/SelectMaskPawn.h"
#include "FindMaskGame/SelectMaskWidget.h"
#include "FindMaskGame/MaskGameBodyActor.h"
#include "FindMaskGame/MaskGameMaskActor.h"
#include "CTPlayerController.h"
#include "InteractiveMeshComponent.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateBrush.h"
#include "Components/Image.h"

ASelectMaskPawn::ASelectMaskPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	static ConstructorHelpers::FClassFinder<USelectMaskWidget> SelectMaskWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_SelectMask.WBP_SelectMask_C'"));
	if (SelectMaskWidgetClass.Succeeded())
	{
		SelectMaskWidgetSubClass = SelectMaskWidgetClass.Class;
	}
}

void ASelectMaskPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (SelectMaskWidgetSubClass != nullptr)
	{
		SelectMaskWidget = Cast<USelectMaskWidget>(CreateWidget(GetWorld(), SelectMaskWidgetSubClass));
		if (SelectMaskWidget != nullptr)
		{
			SelectMaskWidget->AddToViewport();
			SelectMaskWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	BodyNum = 3;
}

void ASelectMaskPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectMaskPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("SelectMask"), IE_Pressed, this, &ASelectMaskPawn::SelectMask);
}

void ASelectMaskPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(SelectMaskWidget))
	{
		SelectMaskWidget->SetVisibility(ESlateVisibility::Visible);

		ACTPlayerController* CTPlayerController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CTPlayerController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Casting Error ASelectMaskPawn"));
			return;
		}
		CTPlayerController->bShowMouseCursor = true;

		if (SelectMaskWidget->GetMaskImageArray().Num() != 0)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(SelectMaskWidget->GetMaskImageArray()[0]);
			SelectMaskWidget->MaskImage->SetBrush(Brush);
		}
	}
}

void ASelectMaskPawn::UnPossessed()
{
	Super::UnPossessed();
	if (IsValid(SelectMaskWidget))
	{
		SelectMaskWidget->SetVisibility(ESlateVisibility::Hidden);

		ACTPlayerController* CTPlayerController = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CTPlayerController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Casting Error ASelectMaskPawn"));
			return;
		}
		CTPlayerController->bShowMouseCursor = false;
	}

}

TMap<class AMaskGameMaskActor*, class UImage*> ASelectMaskPawn::GetMaskMap()
{
	return MaskMap;
}

TArray<class AMaskGameMaskActor*> ASelectMaskPawn::GetMaskArray()
{
	return MaskArray;
}

AMaskGameBodyActor* ASelectMaskPawn::GetCurrentSelectedBody()
{
	return CurrentSelectedBody;
}

AMaskGameMaskActor* ASelectMaskPawn::GetCurrentSelectedMask()
{
	return CurrentSelectedMask;
}

void ASelectMaskPawn::SetCurrentSelectedBody(AMaskGameBodyActor* BodyActor)
{
	CurrentSelectedBody = BodyActor;
}

void ASelectMaskPawn::SetCurrentSelectedMask(AMaskGameMaskActor* MaskActor)
{
	CurrentSelectedMask = MaskActor;
}

USelectMaskWidget* ASelectMaskPawn::GetMaskGameWidget()
{
	return SelectMaskWidget;
}

void ASelectMaskPawn::SelectMask()
{
	if (SelectMaskWidget->GetMaskImageArray()[SelectMaskWidget->CurVisibleImageIndex] == CurrentSelectedBody->CorrectMask->MaskImage)
	{
		BodyNum -= 1;

		UE_LOG(LogTemp, Warning, TEXT("Correct!"));
		if (CurrentSelectedBody->CorrectBody)
		{
			CurrentSelectedBody->GetBodyMesh()->SetStaticMesh(CurrentSelectedBody->CorrectBody);
			SelectMaskWidget->RemoveMaskImage(SelectMaskWidget->GetMaskImageArray()[SelectMaskWidget->CurVisibleImageIndex]);
		}
		
		if (BodyNum == 0)
		{
			SelectMaskWidget->Successed();
		}
	}
}