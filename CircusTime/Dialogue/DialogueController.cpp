#include "Dialogue/DialogueController.h"
#include "CTPlayerCharacter.h"
#include "CTPlayerController.h"
#include "Sound/SoundCue.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UDialogueController::UDialogueController()
{
	DialogueWidget = CreateDefaultSubobject<UDialogueWidget>(TEXT("PlayerWidget"));

	static ConstructorHelpers::FClassFinder<UDialogueWidget> FDialogueWidgetBP(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_Dialogue.WBP_Dialogue_C'"));
	if (FDialogueWidgetBP.Succeeded())
	{
		DialogueWidgetBP = FDialogueWidgetBP.Class;
	}
}

void UDialogueController::Init()
{
	if (DialogueWidgetBP != nullptr)
	{
		DialogueWidget = Cast<UDialogueWidget>(CreateWidget(GetWorld(), DialogueWidgetBP));
		if (DialogueWidget != nullptr)
		{
			DialogueWidget->AddToViewport();
			DialogueWidget->SetActiveDialogueUI(false);
		}
	}

	ACTPlayerController* PC = Cast<ACTPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PlayerAudioComp = PC->GetAudioComponent();
	}
}

void UDialogueController::PlayDialogue(TArray<FDialogueData> DialogueDatas, bool bMovable, bool bTypingEffect)
{
	if (!DialogueDataQueue.IsEmpty())
	{
		return;
	}

	for (FDialogueData DialogueData : DialogueDatas)
	{
		DialogueDataQueue.Enqueue(DialogueData);
	}

	DialogueWidget->SetActiveDialogueUI(true);

	//MovablePlayer(bMovable);
	PrintDialogue(bTypingEffect);
}

void UDialogueController::PrintDialogue(bool bTypingEffect)
{
	if (bTypingEffect)
	{
		PrintTypedEffectDialogue();
		return;
	}
	else
	{
		PrintNormalDialogue();
		GetWorld()->GetTimerManager().SetTimer(NextDialogueTimer, this, &UDialogueController::PrintNormalDialogue, 3.5f, true);
		return;
	}
}

void UDialogueController::PrintNormalDialogue()
{
	if (DialogueDataQueue.IsEmpty())
	{
		//PlayerAudioComp->Stop();
		//MovablePlayer(true);
		DialogueWidget->SetActiveDialogueUI(false);
		GetWorld()->GetTimerManager().ClearTimer(NextDialogueTimer);
		return;
	}

	FDialogueData Temp;
	DialogueDataQueue.Dequeue(Temp);
	if (Temp.Sound != nullptr)
	{
		PlayerAudioComp->SetSound(Temp.Sound);
		PlayerAudioComp->Play();
	}
	DialogueWidget->SetDialogueText(Temp.Text);
}

void UDialogueController::PrintTypedEffectDialogue()
{
	if (DialogueDataQueue.IsEmpty())
	{
		//MovablePlayer(true);
		DialogueWidget->SetActiveDialogueUI(false);
		return;
	}

	FDialogueData Temp;
	DialogueDataQueue.Dequeue(Temp);
	if (Temp.Sound != nullptr)
	{
		PlayerAudioComp->SetSound(Temp.Sound);
		PlayerAudioComp->Play();
		DialogueWidget->PlayTextTypingEffect(Temp.Text, Temp.Sound->Duration);
		GetWorld()->GetTimerManager().SetTimer(NextDialogueTimer, this, &UDialogueController::PrintTypedEffectDialogue, Temp.Sound->Duration + 0.3f, false);
	}
}

void UDialogueController::MovablePlayer(bool bMovable)
{
	ACTPlayerCharacter* Player = Cast<ACTPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!bMovable)
	{
		if (Player)
		{
			Player->DisablePlayerInput(false);
		}
	}
	else
	{
		if (Player)
		{
			Player->EnablePlayerInput();
		}
	}
}