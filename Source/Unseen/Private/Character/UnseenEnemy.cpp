// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UnseenEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"

void AUnseenEnemy::SetEnemyDetectionState(EEnemyDetectionState NewState)
{
	check(EnemyStateInfo);
	SetEnemyDetectionInfoByState(NewState);
	EnemyDetectionStateSet();
}

void AUnseenEnemy::BeginPlay()
{
	Super::BeginPlay();
	SetEnemyDetectionState(EnemyDetectionState);

}

void AUnseenEnemy::SetEnemyDetectionInfoByState(EEnemyDetectionState NewState)
{
	check(EnemyStateInfo)
	const FEnemyDetectionStateInfo* StateInfo = EnemyStateInfo->FindEnemyDetectionStateInfo(NewState);
	MaterialTintColor = StateInfo->Color;
	Image = StateInfo->Image;
	GetCharacterMovement()->MaxWalkSpeed = StateInfo->MovementSpeed;
}
