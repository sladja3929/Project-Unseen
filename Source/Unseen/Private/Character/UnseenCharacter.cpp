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
	// 적의 위치 가져오기
	FVector EnemyPosition = Enemy->GetActorLocation();
        
	// 적의 뒤쪽 방향 벡터 계산
	FVector EnemyForward = Enemy->GetActorForwardVector();
        
	// 뒤쪽으로 이동할 위치 계산 (오프셋 추가)
	FVector BehindPosition = EnemyPosition - (EnemyForward * BackAttackOffset);
        
	// 플레이어의 위치를 적의 뒤쪽으로 설정
	SetActorLocation(BehindPosition);

	// 회전 설정 (적 방향으로 바라보게)
	FRotator TargetRotation = FRotationMatrix::MakeFromX(EnemyForward).Rotator();
	SetActorRotation(TargetRotation);
}
