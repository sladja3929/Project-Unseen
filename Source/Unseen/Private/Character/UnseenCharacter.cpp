// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/UnseenCharacter.h"

AUnseenCharacter::AUnseenCharacter()
{

}
bool AUnseenCharacter::CheckBackPosition()
{
	UE_LOG(LogTemp, Log, TEXT("back"));
	
	return true;
}