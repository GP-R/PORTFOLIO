#pragma once

#include "CoreMinimal.h"
#include "InteractiveMeshComponent.h"
#include "ObjectZoomComponent.generated.h"

USTRUCT()
struct FExploreObjectData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CIRCUSTIME_API UObjectZoomComponent : public UInteractiveMeshComponent
{
	GENERATED_BODY()

public:
	UObjectZoomComponent();

	UFUNCTION()
	void InteractZoomObject();

	UFUNCTION()
	void ReturnObject();

	UFUNCTION()
	FORCEINLINE FExploreObjectData GetInfo() { return Info; }

private:
	bool CreatePostProcessVolume();

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	FExploreObjectData Info;

	FTransform OriginalTransform;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float DistanceInFrontOfPlayer = 30.0f;

	UPROPERTY()
	class APostProcessVolume* BlurVolume;
};
