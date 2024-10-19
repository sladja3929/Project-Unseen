// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/UnseenCharacter.h"

#include "Character/UnseenEnemy.h"

AUnseenCharacter::AUnseenCharacter()
{
	CanBackAttack = false;
	Enemy = nullptr;
}
bool AUnseenCharacter::CheckBackAttackAble()
{	
	return CanBackAttack;
}

void AUnseenCharacter::SetBackAttack(bool IsBackPosition, AUnseenEnemy* Enem)
{
	CanBackAttack = IsBackPosition;
	Enemy = Enem;
}

void AUnseenCharacter::OnBackAttack()
{
	Enemy->OnBackAttackEvent.Broadcast();
}
