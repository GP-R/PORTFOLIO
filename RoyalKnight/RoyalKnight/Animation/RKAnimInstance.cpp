#include "Animation/RKAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URKAnimInstance::URKAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
	GroundSpeed = 0.0f;
	bIsIdle = false;
	bIsFalling = false;
	bIsJumping = false;
}

void URKAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void URKAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
		bIsAccelerating = Movement->GetCurrentAcceleration().Length() > 0.0f;
	}
}
