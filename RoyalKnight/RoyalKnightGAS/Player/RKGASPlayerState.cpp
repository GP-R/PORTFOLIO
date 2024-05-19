#include "Player/RKGASPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attribute/RKCharacterAttributeSet.h"
#include "Player/RKGASPlayerController.h"
#include "UI/RKGASHUDWidget.h"
#include "Inventory/InventoryData.h"
#include "Inventory/PlayerInventory.h"
#include "Inventory/EquipmentInventory.h"
#include "Inventory/UI/EquipmentInventoryWidget.h"

ARKGASPlayerState::ARKGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<URKCharacterAttributeSet>(TEXT("AttributeSet"));
	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>(TEXT("PlayerInventory"));
	EquipmentInventory = CreateDefaultSubobject<UEquipmentInventory>(TEXT("EquipmentInventory"));
}

UAbilitySystemComponent* ARKGASPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

URKCharacterAttributeSet* ARKGASPlayerState::GetAttributeSetBase() const
{
	return AttributeSet;
}

void ARKGASPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (ASC)
	{
		HealthChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ARKGASPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ARKGASPlayerState::MaxHealthChanged);
		
		ManaChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddUObject(this, &ARKGASPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute()).AddUObject(this, &ARKGASPlayerState::MaxManaChanged);
		
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetAttackRateAttribute()).AddUObject(this, &ARKGASPlayerState::AttackRateChanged);
	
	}

	PlayerInventory->Init();
	EquipmentInventory->Init();
}

float ARKGASPlayerState::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ARKGASPlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float ARKGASPlayerState::GetMana() const
{
	return AttributeSet->GetMana();
}

float ARKGASPlayerState::GetMaxMana() const
{
	return AttributeSet->GetMaxMana();
}

float ARKGASPlayerState::GetAttackRate() const
{
	return AttributeSet->GetAttackRate();
}

void ARKGASPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	ARKGASPlayerController* PC = Cast<ARKGASPlayerController>(GetOwner());
	if (PC)
	{
		URKGASHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetCurrentHealth(Data.NewValue);
		}
	}
}

void ARKGASPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	ARKGASPlayerController* PC = Cast<ARKGASPlayerController>(GetOwner());
	if (PC)
	{
		URKGASHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxHealth(Data.NewValue);
		}

		UEquipmentInventoryWidget* Widget = PC->GetEquipmentInventory();
		if (Widget)
		{
			Widget->SetMaxHealthText(Data.NewValue);
		}
	}
}

void ARKGASPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	ARKGASPlayerController* PC = Cast<ARKGASPlayerController>(GetOwner());
	if (PC)
	{
		URKGASHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetCurrentMana(Data.NewValue);
		}
	}
}

void ARKGASPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	ARKGASPlayerController* PC = Cast<ARKGASPlayerController>(GetOwner());
	if (PC)
	{
		URKGASHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxMana(Data.NewValue);
		}

		UEquipmentInventoryWidget* Widget = PC->GetEquipmentInventory();
		if (Widget)
		{
			Widget->SetMaxManaText(Data.NewValue);
		}
	}
}

void ARKGASPlayerState::AttackRateChanged(const FOnAttributeChangeData& Data)
{
	ARKGASPlayerController* PC = Cast<ARKGASPlayerController>(GetOwner());
	if (PC)
	{
		UEquipmentInventoryWidget* Widget = PC->GetEquipmentInventory();
		if (Widget)
		{
			Widget->SetAttackRateText(Data.NewValue);
		}
	}
}
