// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UnseenEnemy.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AUnseenEnemy::AUnseenEnemy()
{	
	HeadStateIcon = CreateDefaultSubobject<UWidgetComponent>("HeadStateIcon");
	HeadStateIcon->SetupAttachment(GetRootComponent());

	CombatGaugeTest = CreateDefaultSubobject<UWidgetComponent>("CombatGaugeTest");
	CombatGaugeTest->SetupAttachment(GetRootComponent());
	
}

void AUnseenEnemy::BeginPlay()
{
	Super::BeginPlay();
	SetEnemyDetectionState(EnemyDetectionState);
	
}

void AUnseenEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(HeadStateIcon)
	{
		FVector IconLocation = HeadStateIcon->GetComponentLocation();
		FVector CameraLocation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();
		FRotator IconRotator = (CameraLocation-IconLocation).Rotation();
		
		HeadStateIcon->SetWorldRotation(IconRotator);
	}

	if(CombatGaugeTest)
	{
		FVector IconLocation = CombatGaugeTest->GetComponentLocation();
		FVector CameraLocation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();
		FRotator IconRotator = (CameraLocation-IconLocation).Rotation();
		
		CombatGaugeTest->SetWorldRotation(IconRotator);
	}
}

/*  
 * TODO: 적 캐릭터는 각각의 게이지가 있고, 게이지가 차면 Combat으로 바뀜
 *			게이지가 차려면 보거나 무슨 일이 있거나 하는 식으로 해야함
 *			옆에서 걸어 다니거나 해도 게이지가 차도록 하기
 */

void AUnseenEnemy::SetEnemyDetectionState(EEnemyDetectionState NewState)
{
	check(EnemyStateInfo);
	SetEnemyDetectionInfoByState(NewState);
	EnemyDetectionStateSet();
}

void AUnseenEnemy::SetEnemyDetectionInfoByState(EEnemyDetectionState NewState)
{
	check(EnemyStateInfo)
	const FEnemyDetectionStateInfo* StateInfo = EnemyStateInfo->FindEnemyDetectionStateInfo(NewState);
	MaterialTintColor = StateInfo->Color;
	Image = StateInfo->Image;
	GetCharacterMovement()->MaxWalkSpeed = StateInfo->MovementSpeed;
}
