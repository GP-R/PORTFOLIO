// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CTPlayerCharacter.generated.h"

USTRUCT()
struct FPlayerCameraShakes
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, meta = (ToolTip = "A camera shake to play while in an idle state"), Category = "Shakes")
	TSubclassOf<class UMatineeCameraShake> IdleShake;

	UPROPERTY(EditInstanceOnly, meta = (ToolTip = "A camera shake to play while walking"), Category = "Shakes")
	TSubclassOf<class UMatineeCameraShake> WalkShake;

	UPROPERTY(EditInstanceOnly, meta = (ToolTip = "A camera shake to play while running"), Category = "Shakes")
	TSubclassOf<class UMatineeCameraShake> RunShake;
};

USTRUCT()
struct FPlayerFootstepSettings
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "Footstep", meta = (ToolTip = "Enable/Disable the ability to play footsteps?"))
	bool bEnableFootsteps = true;

	UPROPERTY(EditAnywhere, Category = "Footstep", meta = (EditCondition = "bEnableFootsteps", ToolTip = "An array of footstep data assets to play depending on the material the character is moving on"))
	TArray<class UPlayerFootstepData*> Mappings;

	float CurrentStride = 160.0f;
};

USTRUCT()
struct FPlayerMovementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "Movement", meta = (ClampMin = 1.0f, ClampMax = 10000.0f, ToolTip = "The normal movement speed"))
	float WalkSpeed = 300.0f;

	UPROPERTY(EditInstanceOnly, Category = "Movement", meta = (ClampMin = 1.0f, ClampMax = 10000.0f, ToolTip = "The movement speed while running"))
	float RunSpeed = 500.0f;
};

USTRUCT()
struct FPlayerCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "Camera", DisplayName = "Sensitivity (Yaw)", meta = (ClampMin = 0.0f, UIMax = 100.0f, ToolTip = "The sensitivity of the horizontal camera rotation (Yaw). Lower values = Slower camera rotation. Higher values = Faster camera rotation"))
	float SensitivityX = 50.0f;

	UPROPERTY(EditInstanceOnly, Category = "Camera", DisplayName = "Sensitivity (Pitch)", meta = (ClampMin = 0.0f, UIMax = 100.0f, ToolTip = "The sensitivity of the vertical camera rotation (Pitch). Lower values = Slower camera rotation. Higher values = Faster camera rotation"))
	float SensitivityY = 50.0f;

	UPROPERTY(EditInstanceOnly, Category = "Camera", meta = (ClampMin = "-360.0", ClampMax = 360.0f, ToolTip = "The minimum view pitch, in degrees. Some examples are 300.0, 340.0, -90.0, 270.0 or 0.0"))
	float MinPitch = -90.0f;

	UPROPERTY(EditInstanceOnly, Category = "Camera", meta = (ClampMin = "-360.0", ClampMax = 360.0f, ToolTip = "The maximum view pitch, in degrees. Some examples are 20.0, 45.0, 90.0 or 0.0"))
	float MaxPitch = 90.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeftMouseButtonClick);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeftMouseButtonClickRepeat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeftMouseButtonClickReleased);

UCLASS()
class CIRCUSTIME_API ACTPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACTPlayerCharacter();

	UFUNCTION(BlueprintGetter)
	class UCTPlayerWidget* GetPlayerWidget();

	float GetStaminaValue();

	void DisablePlayerInput(bool bActiveWidget);
	void EnablePlayerInput();

	UFUNCTION(BlueprintCallable)
	void SetUseFlashLight(bool bCanUse);

	UFUNCTION(BlueprintCallable)
	void OnInteraction(bool bActiveUI);

	UFUNCTION(BlueprintCallable)
	class UCameraComponent* GetPlayerCamera() { return Camera; }

	UFUNCTION(BlueprintCallable)
	void SetLockRotation(bool bLock) { bLockRotation = bLock; }

	UFUNCTION(BlueprintCallable)
	void SetLockMoving(bool bLock) { bLockMoving = bLock; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerWidgetVisibility(bool bVisible);

	UFUNCTION(BlueprintCallable)
	bool GetZoomMode() { return bZoomMode; }

	void SetZoomMode(bool bValue);

	UFUNCTION()
	void Explore(class UObjectZoomComponent* NewExploreObject);

	UFUNCTION()
	void TurnOnFlashLight();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	void PlayFootstepSound();
	USoundBase* GetFootstepSound(TWeakObjectPtr<UPhysicalMaterial>* Surface);

	void UpdateCameraShake();

private:
	void UpDown(float Value);
	void LeftRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void Interaction();
	void Run();
	void StopRunning();

	void UpdateAim();

	UFUNCTION()
	void LeftMouseButtonClick();

	UFUNCTION()
	void LeftMouseButtonClickRepeat();

	UFUNCTION()
	void LeftMouseButtonClickReleased();

	UFUNCTION()
	void WheelButtonClick();

	UFUNCTION()
	void WheelButtonReleased();

	UFUNCTION()
	void Cancel();

public:
	UPROPERTY(VisibleAnywhere)
	class UInteractiveMeshComponent* InteractionObject;

	UPROPERTY(VisibleAnywhere)
	class UObjectZoomComponent* ZoomObject;

	FLeftMouseButtonClick LeftMouseButtonClickEvent;
	FLeftMouseButtonClickRepeat LeftMouseButtonClickRepeatEvent;
	FLeftMouseButtonClickReleased LeftMouseButtonClickReleasedEvent;

protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USpotLightComponent* FlashLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UCTPlayerWidget> PlayerWidgetAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true, BlueprintGetter = "GetPlayerWidget"))
	class UCTPlayerWidget* PlayerWidget;

	UPROPERTY()
	class UExploreWidget* ExploreWidget;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UExploreWidget> ExploreWidgetBP;

	UPROPERTY(EditAnywhere, Category = "First Person Settings", meta = (ToolTip = "Add one of your custom camera shakes to the corresponding slot"))
	FPlayerCameraShakes CameraShakes;

	UPROPERTY(EditAnywhere, Category = "First Person Settings", meta = (ToolTip = "Adjust these camera settings to your liking"))
	FPlayerCameraSettings CameraSetting;

	UPROPERTY(EditAnywhere, Category = "First Person Settings", meta = (ToolTip = "Adjust these footstep settings to your liking"))
	FPlayerFootstepSettings FootstepSettings;

	UPROPERTY(EditAnywhere, Category = "First Person Settings", meta = (ToolTip = "Adjust these movement settings to your liking"))
	FPlayerMovementSettings Movement;

private:
	class ACTPlayerController* PlayerController;

	UPlayerFootstepData* CurrentFootstepMapping;

	FVector LastFootstepLocation;
	FVector LastLocation;
	FFindFloorResult FloorResult;
	float TravelDistance = 0.0f;

	FVector2D ScreenAimPos;
	float InteractionRange = 300.0f;
	float Stamina = 100.0f;

	FTimerHandle UseStaminaTimerHandle;
	FTimerHandle UnUseStaminaTimerHandle;

	bool bCanInput = true;
	bool bIsRunning = false;
	bool bHasFlashLight = false;
	bool bLockRotation = false;
	bool bLockMoving = false;
	bool bZoomMode = false;
	bool bLeftButtonDown = false;
	bool bWheelButtonDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float ZoomObjectRotationSpeed = 0.1f;

private:
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* OnFlashLightSound;
};
