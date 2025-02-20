#include "Character/RKGASCharacterPlayer.h"
#include "AbilitySystemComponent.h"
#include "Player/RKGASPlayerState.h"
#include "EnhancedInputComponent.h"
#include "Tag/RKGameplayTag.h"
#include "Attribute/RKCharacterAttributeSet.h"
#include "GA/RKGA_SkillBase.h"
#include "Equipment/RKGASWeaponActor.h"
#include "Player/RKGASPlayerController.h"
#include "UI/RKGASHUDWidget.h"
#include "Equipment/RKGASEquipment.h"

#include "Inventory/InventoryBase.h"

ARKGASCharacterPlayer::ARKGASCharacterPlayer()
{
	ASC = nullptr;

	//TODO : Worrior Montage class로 옮기기
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/RoyalKnight/Animation/Worrior/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}
}

UAbilitySystemComponent* ARKGASCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void ARKGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ARKGASPlayerState* GASPS = GetPlayerState<ARKGASPlayerState>();
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		ASC->GenericGameplayEventCallbacks.FindOrAdd(RKTAG_EVENT_CHARACTER_WEAPONEQUIP).AddUObject(this, &ARKGASCharacterPlayer::Equip);
		ASC->GenericGameplayEventCallbacks.FindOrAdd(RKTAG_EVENT_CHARACTER_WEAPONUNEQUIP).AddUObject(this, &ARKGASCharacterPlayer::Unequip);

		const URKCharacterAttributeSet* CurrentAttributeSet = ASC->GetSet<URKCharacterAttributeSet>();
		if (CurrentAttributeSet)
		{
			CurrentAttributeSet->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealth);
		}

		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}

		for (const auto& StartInputAbility : StartInputAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
			StartSpec.InputID = StartInputAbility.Key;
			ASC->GiveAbility(StartSpec);
		}

		FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(InitStatEffect, 1, EffectContextHandle);
		if (EffectSpecHandle.IsValid())
		{
			ASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
		}

		SetupGASInputComponent();

		ARKGASPlayerController* PlayerController = CastChecked<ARKGASPlayerController>(NewController);
		PlayerController->CreateHUD();
		//PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}

void ARKGASCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	SetupGASInputComponent();
}

void ARKGASCharacterPlayer::SetupGASInputComponent()
{
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::GASInputPressed, 0);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARKGASCharacterPlayer::GASInputReleased, 0);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::GASInputPressed, 1);
		EnhancedInputComponent->BindAction(SkillAction_01, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::GASInputPressed, 2);
		EnhancedInputComponent->BindAction(SkillAction_02, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::GASInputPressed, 3);
		EnhancedInputComponent->BindAction(SkillAction_03, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::GASInputPressed, 4);
		EnhancedInputComponent->BindAction(SkillAction_04, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::GASInputPressed, 5);
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::ToggleInventory);
		EnhancedInputComponent->BindAction(ToggleEquipmentInventoryAction, ETriggerEvent::Triggered, this, &ARKGASCharacterPlayer::ToggleEquipmentInventory);
	}
}

void ARKGASCharacterPlayer::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void ARKGASCharacterPlayer::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}

void ARKGASCharacterPlayer::OnOutOfHealth()
{
	SetDead();
}

void ARKGASCharacterPlayer::Equip(const FGameplayEventData* EventData)
{
	if (EventData->OptionalObject)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		UClass* EquipmentClass = Cast<UClass>(EventData->OptionalObject);
		ARKGASEquipment* EquipmentActor	= GetWorld()->SpawnActor<ARKGASEquipment>(EquipmentClass, SpawnParameters);
		if (EquipmentActor)
		{
			EquippedItems.Add(EquipmentActor);
			if (EquipmentActor->GetEquipmentType() == EEquipmentType::Helmet)
			{
				EquipmentActor->Equip(this, HelmetSocketName);
			}
			else if (EquipmentActor->GetEquipmentType() == EEquipmentType::Armor)
			{
				EquipmentActor->Equip(this, ArmorSocketName);
			}
			else if (EquipmentActor->GetEquipmentType() == EEquipmentType::Pants)
			{
				EquipmentActor->Equip(this, PantsSocketName);
			}
			else if (EquipmentActor->GetEquipmentType() == EEquipmentType::Shoes)
			{
				EquipmentActor->Equip(this, ShoesSocketName);
			}
			else if (EquipmentActor->GetEquipmentType() == EEquipmentType::Weapon)
			{
				EquipmentActor->Equip(this, WeaponSocketName);
			}
			else if (EquipmentActor->GetEquipmentType() == EEquipmentType::Gloves)
			{
				EquipmentActor->Equip(this, GlovesSocketName);
			}
			else if (EquipmentActor->GetEquipmentType() == EEquipmentType::Neck)
			{
				EquipmentActor->Equip(this, NeckSocketName);
			}
			else if (EquipmentActor->GetEquipmentType() == EEquipmentType::Ring)
			{
				EquipmentActor->Equip(this, RingSocketName);
			}
		}
	}
}

void ARKGASCharacterPlayer::Unequip(const FGameplayEventData* EventData)
{
	if (!EventData->OptionalObject)
	{
		return;
	}

	for (ARKGASEquipment* Item : EquippedItems)
	{
		if (Item->StaticClass() == Cast<UClass>(EventData->OptionalObject))
		{
			Item->UnEquip();
		}
	}
}

void ARKGASCharacterPlayer::ToggleInventory()
{
	ARKGASPlayerController* PlayerController = CastChecked<ARKGASPlayerController>(GetController());
	PlayerController->ToggleInventory();
}

void ARKGASCharacterPlayer::ToggleEquipmentInventory()
{
	ARKGASPlayerController* PlayerController = CastChecked<ARKGASPlayerController>(GetController());
	PlayerController->ToggleEquipmentInventory();
}
