#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BodyPanel.generated.h"

UCLASS()
class CIRCUSTIME_API ABodyPanel : public AActor
{
	GENERATED_BODY()

public:
	ABodyPanel();

	void CombineMask();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Interacted();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UInteractiveMeshComponent* BodyMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* CameraPosition;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	ABodyPanel* NextBodyPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	ABodyPanel* PrevBodyPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class AMaskGameMaskActor* CorrectMask;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* CorrectBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ASelectMaskPawn> SelectMaskPawnBP;
};
