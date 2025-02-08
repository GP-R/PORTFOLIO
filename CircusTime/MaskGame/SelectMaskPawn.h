#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SelectMaskPawn.generated.h"

UCLASS()
class CIRCUSTIME_API ASelectMaskPawn : public APawn
{
	GENERATED_BODY()

public:
	ASelectMaskPawn();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

public:
	UFUNCTION()
	TMap<class AMaskGameMaskActor*, class UImage*> GetMaskMap();

	UFUNCTION()
	TArray<class AMaskGameMaskActor*> GetMaskArray();

	UFUNCTION()
	class AMaskGameBodyActor* GetCurrentSelectedBody();

	UFUNCTION()
	class AMaskGameMaskActor* GetCurrentSelectedMask();

	UFUNCTION()
	void SetCurrentSelectedBody(class AMaskGameBodyActor* BodyActor);

	UFUNCTION()
	void SetCurrentSelectedMask(class AMaskGameMaskActor* MaskActor);

	UFUNCTION()
	class USelectMaskWidget* GetMaskGameWidget();

private:
	UFUNCTION()
	void SelectMask();

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class USelectMaskWidget> SelectMaskWidgetSubClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class USelectMaskWidget* SelectMaskWidget;

	UPROPERTY()
	TMap<class AMaskGameMaskActor*, class AMaskGameBodyActor*> BodyMap;

	UPROPERTY()
	TMap<class AMaskGameMaskActor*, class UImage*> MaskMap;

	UPROPERTY()
	TArray<class AMaskGameMaskActor*> MaskArray;

	UPROPERTY()
	class AMaskGameBodyActor* CurrentSelectedBody;

	UPROPERTY()
	class AMaskGameMaskActor* CurrentSelectedMask;

	int BodyNum;
};
