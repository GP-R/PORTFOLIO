#include "Equipment/RKGASEquipment.h"
#include "AbilitySystemBlueprintLibrary.h"
#include <AbilitySystemComponent.h>
#include "Character/RKGASCharacterPlayer.h"

ARKGASEquipment::ARKGASEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
	EquipmentMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipmentMesh"));
}

void ARKGASEquipment::Equip(AActor* Target, FName SocketName)
{
	if (EquipmentMesh)
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		ARKGASCharacterPlayer* Temp = Cast<ARKGASCharacterPlayer>(Target);
		if (Temp)
		{
			EquipmentMesh->AttachToComponent(Temp->GetMesh(), AttachmentRules, SocketName);
		}
	}

	if (EquipmentEffect)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
		if (TargetASC)
		{
			FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(EquipmentEffect, 1, EffectContext);
			if (EffectSpecHandle.IsValid())
			{
				TargetASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
			}
		}
	}
}

void ARKGASEquipment::UnEquip()
{
	Destroyed();
}

void ARKGASEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARKGASEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

