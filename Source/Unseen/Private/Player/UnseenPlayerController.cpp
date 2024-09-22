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
#include "Character/UnseenCharacter.h"

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
	MaxWalkSpeed = GetCharacter()->GetCharacterMovement()->MaxWalkSpeed;

	UnseenAnim = Cast<UUnseenAnimInstance>(GetCharacter()->GetMesh()->GetAnimInstance());
	check(nullptr != UnseenAnim);
	UnseenAnim->OnBackAttackEnd.AddUFunction(this, FName("BackAttackEnd"));
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

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AUnseenPlayerController::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AUnseenPlayerController::StopSprinting);

		EnhancedInputComponent->BindAction(BackAttackAction, ETriggerEvent::Started, this, &AUnseenPlayerController::BackAttack);
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
			if (IsCrouch)
			{
				ControlledCharacter->UnCrouch();
			}


			else
			{
				ControlledCharacter->Crouch();
			}

			IsCrouch = !IsCrouch;
		}
		
	}
	
}

void AUnseenPlayerController::Sprint()
{
	if (ACharacter* ControlledCharacter = GetCharacter())
	{
		if (!IsCrouch)
		{
			ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed * 2.0f;
		}
		
	}
}

void AUnseenPlayerController::StopSprinting()
{
	if (ACharacter* ControlledCharacter = GetCharacter())
	{
		ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}

void AUnseenPlayerController::BackAttack()
{
	if(ACharacter* ControlledCharacter = GetCharacter())
	{
		AUnseenCharacter* Un = Cast<AUnseenCharacter>(ControlledCharacter);
		if(Un->CheckBackPosition())
		{
			IsBackAttack = true;
			SetIgnoreMoveInput(true);
		}
	}
}

void AUnseenPlayerController::BackAttackEnd()
{
	IsBackAttack = false;
	SetIgnoreMoveInput(false);
}

bool AUnseenPlayerController::IsBackAttacking()
{
	return IsBackAttack;
}
