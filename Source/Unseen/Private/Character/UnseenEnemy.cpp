// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UnseenEnemy.h"

#include "Character/UnseenCharacter.h"
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
	BackArea = FindComponentByClass<UBoxComponent>();
	
	BackArea->OnComponentBeginOverlap.AddDynamic(this, &AUnseenEnemy::OnComponentBeginOverlap);
}

void AUnseenEnemy::SetEnemyDetectionInfoByState(EEnemyDetectionState NewState)
{
	check(EnemyStateInfo)
	const FEnemyDetectionStateInfo* StateInfo = EnemyStateInfo->FindEnemyDetectionStateInfo(NewState);
	MaterialTintColor = StateInfo->Color;
	Image = StateInfo->Image;
	GetCharacterMovement()->MaxWalkSpeed = StateInfo->MovementSpeed;
}

void AUnseenEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AUnseenCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy overlapped with Player"));
		// 여기에 원하는 로직 추가 (예: 데미지 처리, 이벤트 발생 등)
	}
}