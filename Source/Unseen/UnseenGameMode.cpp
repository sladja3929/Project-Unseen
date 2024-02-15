// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnseenGameMode.h"
#include "UnseenCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnseenGameMode::AUnseenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
