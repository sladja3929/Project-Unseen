// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UnseenPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"


void AUnseenPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(DefaultMappingContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	GetCharacter()->GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AUnseenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUnseenPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUnseenPlayerController::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AUnseenPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AUnseenPlayerController::StopJumping);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AUnseenPlayerController::ToggleCrouch);
	}
}

void AUnseenPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);
	const FVector ForwardDirection = RotationMatrix.GetUnitAxis(EAxis::X);
	const FVector RightDirection = RotationMatrix.GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AUnseenPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2d LookAxisVector = InputActionValue.Get<FVector2d>();
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUnseenPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if(ACharacter* ControlledCharacter = GetCharacter())
	{
		ControlledCharacter->Jump();
	}
}

void AUnseenPlayerController::StopJumping(const FInputActionValue& InputActionValue)
{
	if(ACharacter* ControlledCharacter = GetCharacter())
	{
		ControlledCharacter->StopJumping();
	}
}

AUnseenPlayerController::AUnseenPlayerController()
{
}

void AUnseenPlayerController::ToggleCrouch()
{
	if (ACharacter* ControlledCharacter = GetCharacter())
	{
		if (!ControlledCharacter->GetCharacterMovement()->IsFalling())
		{
			IsCrouch = !IsCrouch;

			if (IsCrouch)
			{
				ControlledCharacter->UnCrouch();
			}


			else
			{
				ControlledCharacter->Crouch();
			}
		}
		
	}
	
}

void AUnseenPlayerController::SmoothCrouchInterpReturn(float Value)
{
	
	if (ACharacter* ControlledCharacter = GetCharacter())
	{
		//ControlledCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::Lerp(88.f, ControlledCharacter->CrouchHeight, Value));
		//FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 10.0f, (FMath::Lerp(160.0f, 120.0f, Value))));
	}
	
}

void AUnseenPlayerController::SmoothCrouchOnFinish()
{
	// ���ϸ� �ۼ�
}

void AUnseenPlayerController::SmoothCrouchTimelineSetting()
{
	if (SmoothCrouchingCurveFloat)
	{
		SmoothCrouchingCurveTimeline->AddInterpFloat(SmoothCrouchingCurveFloat, SmoothCrouchInterpFunction);
		SmoothCrouchingCurveTimeline->SetTimelineFinishedFunc(SmoothCrouchTimelineFinish);
		SmoothCrouchingCurveTimeline->SetLooping(false);
	}
}

void AUnseenPlayerController::StartCrouch()
{
	SmoothCrouchingCurveTimeline->Play();
}