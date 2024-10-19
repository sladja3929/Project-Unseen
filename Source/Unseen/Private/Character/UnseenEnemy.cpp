// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UnseenEnemy.h"

#include "Components/WidgetComponent.h"
#include "Character/UnseenCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AUnseenEnemy::AUnseenEnemy()
{	
	HeadStateIcon = CreateDefaultSubobject<UWidgetComponent>("HeadStateIcon");
	HeadStateIcon->SetupAttachment(GetRootComponent());

	CombatGaugeTest = CreateDefaultSubobject<UWidgetComponent>("CombatGaugeTest");
	CombatGaugeTest->SetupAttachment(GetRootComponent());

	BackArea = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BackArea->SetupAttachment(GetRootComponent());

	CollisionComponent = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
	
	BackArea->SetBoxExtent(FVector(30.0f, 40.0f, 95.0f));
	BackArea->SetRelativeLocation(FVector(-50.0f, 0.0f, 0.0f));
	BackArea->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	OnBackAttackEvent.AddUFunction(this, FName("OnBackAttacked"));
}

void AUnseenEnemy::BeginPlay()
{
	Super::BeginPlay();	
	SetEnemyDetectionState(EnemyDetectionState);	
	
	BackArea->OnComponentBeginOverlap.AddDynamic(this, &AUnseenEnemy::OnComponentBeginOverlap);
	BackArea->OnComponentEndOverlap.AddDynamic(this, &AUnseenEnemy::OnComponentEndOverlap);
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

void AUnseenEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AUnseenCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Can BackAttack"));
		AUnseenCharacter* Unseen = Cast<AUnseenCharacter>(OtherActor);
		Unseen->SetBackAttack(true, this);		
	}
}

void AUnseenEnemy::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(AUnseenCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Exit BackAttack"));
		AUnseenCharacter* Unseen = Cast<AUnseenCharacter>(OtherActor);
		Unseen->SetBackAttack(false, nullptr);
	}
}

bool AUnseenEnemy::IsBackAttacked()
{
	return IsBackAttack;
}

void AUnseenEnemy::OnBackAttacked()
{
	IsBackAttack = true;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UE_LOG(LogTemp, Warning, TEXT("Dead"));
}
