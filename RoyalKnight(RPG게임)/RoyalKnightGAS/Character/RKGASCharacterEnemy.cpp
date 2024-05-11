#include "Character/RKGASCharacterEnemy.h"
#include "AbilitySystemComponent.h"
#include "Attribute/RKCharacterAttributeSet.h"
#include "UI/RKGASWidgetComponent.h"
#include "UI/RKGASUserWidget.h"

ARKGASCharacterEnemy::ARKGASCharacterEnemy()
{
    ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
    AttributeSet = CreateDefaultSubobject<URKCharacterAttributeSet>(TEXT("AttributeSet"));

	HpBar = CreateDefaultSubobject<URKGASWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/RoyalKnight/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(200.0f, 20.f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	Level = 1;
}

UAbilitySystemComponent* ARKGASCharacterEnemy::GetAbilitySystemComponent() const
{
    return ASC;
}

void ARKGASCharacterEnemy::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    ASC->InitAbilityActorInfo(this, this);
	AttributeSet->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealth);

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(InitStatEffect, Level, EffectContextHandle);
	if (EffectSpecHandle.IsValid())
	{
		ASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
	}
}

void ARKGASCharacterEnemy::OnOutOfHealth()
{
	SetDead();
}
