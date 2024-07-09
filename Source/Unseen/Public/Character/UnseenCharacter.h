// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/UnseenCharacterBase.h"
#include "UnseenCharacter.generated.h"

class UCameraComponent;

UCLASS()
class AUnseenCharacter : public AUnseenCharacterBase
{
	GENERATED_BODY()

protected:

	//virtual void BeginPlay() override;

public:
	AUnseenCharacter();
	void gea();

};

