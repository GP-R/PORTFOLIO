#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/RKCharacterBase.h"
#include "RKGASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROYALKNIGHTGAS_API ARKGASPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void CreateHUD();
	void CreateInventoryWidget();
	void CreateEquipmentInventoryWidget();

	//UPROPERTY(EditAnywhere, Category = "GASDocumentation|UI")
	//TSubclassOf<class UGDDamageTextWidgetComponent> DamageNumberClass;

	class URKGASHUDWidget* GetHUD();
	class UPlayerInventoryWidget* GetPlayerInventory();
	class UEquipmentInventoryWidget* GetEquipmentInventory();

	UFUNCTION(Client, Reliable, WithValidation)
	void ShowDamageNumber(float DamageAmount, ARKCharacterBase* TargetCharacter);
	void ShowDamageNumber_Implementation(float DamageAmount, ARKCharacterBase* TargetCharacter);
	bool ShowDamageNumber_Validate(float DamageAmount, ARKCharacterBase* TargetCharacter);

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

	UFUNCTION(BlueprintCallable)
	void ToggleEquipmentInventory();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class URKGASHUDWidget> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class URKGASHUDWidget* UIHUDWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UPlayerInventoryWidget> InventoryWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UPlayerInventoryWidget* InventoryWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UEquipmentInventoryWidget> EquipmentInventoryWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UEquipmentInventoryWidget* EquipmentInventoryWidget;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;
};
