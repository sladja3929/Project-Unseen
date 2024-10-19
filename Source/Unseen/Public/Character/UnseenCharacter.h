// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnseenEnemy.h"
#include "Character/UnseenCharacterBase.h"
#include "UnseenCharacter.generated.h"

class UCameraComponent;

UCLASS()
class AUnseenCharacter : public AUnseenCharacterBase
{
	GENERATED_BODY()

private:
	bool CanBackAttack;
	AUnseenEnemy* Enemy;
	
protected:
	
	//virtual void BeginPlay() override;

public:	
	
	AUnseenCharacter();

	UFUNCTION(BlueprintCallable, Category = "Move")
	bool CheckBackAttackAble();

	void SetBackAttack(bool IsBackPosition, AUnseenEnemy* Enem);

	void OnBackAttack();
};

