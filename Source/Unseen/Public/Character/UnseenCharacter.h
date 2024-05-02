// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UnseenCharacterBase.h"
#include "UnseenCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API AUnseenCharacter : public AUnseenCharacterBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Test")
	float Test = 0.f;
};
