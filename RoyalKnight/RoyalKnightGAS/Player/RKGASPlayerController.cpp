#include "Player/RKGASPlayerController.h"
#include "Player/RKGASPlayerState.h"
#include "UI/RKGASHUDWidget.h"
#include "AbilitySystemComponent.h"
#include "RoyalKnightGASModule.h"
#include "Inventory/InventoryData.h"

#include "Inventory/UI/InventoryWidget.h"
#include "Inventory/UI/PlayerInventoryWidget.h"
#include "Inventory/PlayerInventory.h"

#include "Inventory/UI/EquipmentInventoryWidget.h"
#include "Inventory/EquipmentInventory.h"

void ARKGASPlayerController::CreateHUD()
{
	if (UIHUDWidget)
	{
		return;
	}

	if (!UIHUDWidgetClass)
	{
		return;
	}

	if (!IsLocalPlayerController())
	{
		return;
	}

	ARKGASPlayerState* GASPS = GetPlayerState<ARKGASPlayerState>();
	if (!GASPS)
	{
		return;
	}

	UIHUDWidget = CreateWidget<URKGASHUDWidget>(this, UIHUDWidgetClass);
	UIHUDWidget->AddToViewport();

	UIHUDWidget->SetCurrentHealth(GASPS->GetHealth());
	UIHUDWidget->SetMaxHealth(GASPS->GetMaxHealth());
	UIHUDWidget->SetHealthPercentage(GASPS->GetHealth() / FMath::Max<float>(GASPS->GetMaxHealth(), 1.f));

	UIHUDWidget->SetCurrentMana(GASPS->GetMana());
	UIHUDWidget->SetMaxMana(GASPS->GetMaxMana());
	UIHUDWidget->SetManaPercentage(GASPS->GetMana() / FMath::Max<float>(GASPS->GetMaxMana(), 1.f));

}

void ARKGASPlayerController::CreateInventoryWidget()
{
	if (InventoryWidget)
	{
		return;
	}

	if (!InventoryWidgetClass)
	{
		return;
	}

	ARKGASPlayerState* GASPS = GetPlayerState<ARKGASPlayerState>();
	if (!GASPS)
	{
		return;
	}

	InventoryWidget = CreateWidget<UPlayerInventoryWidget>(this, InventoryWidgetClass);
	InventoryWidget->AddToViewport();
	
	InventoryWidget->Init();
	InventoryWidget->CreateItemSlots(30, 5);

	UPlayerInventory* PlayerInventory = GASPS->GetPlayerInventory();
	if (PlayerInventory)
	{
		InventoryWidget->SetEquipmentItemData(PlayerInventory->GetEquipmentItems());
		InventoryWidget->SetConsumableItemData(PlayerInventory->GetConsumableItems());
		InventoryWidget->SetETCItemData(PlayerInventory->GetETCItems());
	}

	PlayerInventory->LoadDefaultItems();
}

void ARKGASPlayerController::CreateEquipmentInventoryWidget()
{
	if (EquipmentInventoryWidget)
	{
		return;
	}

	if (!EquipmentInventoryWidgetClass)
	{
		return;
	}

	ARKGASPlayerState* GASPS = GetPlayerState<ARKGASPlayerState>();
	if (!GASPS)
	{
		return;
	}
	EquipmentInventoryWidget = CreateWidget<UEquipmentInventoryWidget>(this, EquipmentInventoryWidgetClass);
	EquipmentInventoryWidget->AddToViewport();

	EquipmentInventoryWidget->Init();

	UEquipmentInventory* EquipmentInventory = GASPS->GetEquipmentInventory();
	if (EquipmentInventory)
	{
		EquipmentInventoryWidget->SetEquippedItemData(EquipmentInventory->GetEquippedItems());
	}
}

URKGASHUDWidget* ARKGASPlayerController::GetHUD()
{
	return UIHUDWidget;
}

UPlayerInventoryWidget* ARKGASPlayerController::GetPlayerInventory()
{
	return InventoryWidget;
}

UEquipmentInventoryWidget* ARKGASPlayerController::GetEquipmentInventory()
{
	return EquipmentInventoryWidget;
}

void ARKGASPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ARKCharacterBase* TargetCharacter)
{
}

bool ARKGASPlayerController::ShowDamageNumber_Validate(float DamageAmount, ARKCharacterBase* TargetCharacter)
{
	return false;
}

void ARKGASPlayerController::ToggleInventory()
{
	if (InventoryWidget == nullptr)
	{
		CreateInventoryWidget();
	}

	if (InventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		SetShowMouseCursor(true);
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->GetCachedWidget());
		SetInputMode(InputMode);
		IgnoreLookInput = true;
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		IgnoreLookInput = false;
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void ARKGASPlayerController::ToggleEquipmentInventory()
{
	if (EquipmentInventoryWidget == nullptr)
	{
		CreateEquipmentInventoryWidget();
	}

	if (EquipmentInventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		SetShowMouseCursor(true);
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(EquipmentInventoryWidget->GetCachedWidget());
		SetInputMode(InputMode);
		IgnoreLookInput = true;
		EquipmentInventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		IgnoreLookInput = false;
		EquipmentInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ARKGASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RKGAS_LOG(LogRKGAS, Log, TEXT("OnPossess"));
	ARKGASPlayerState* GASPS = GetPlayerState<ARKGASPlayerState>();
	if (GASPS)
	{
		GASPS->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPS, InPawn);
	}
}

void ARKGASPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CreateHUD();
}
