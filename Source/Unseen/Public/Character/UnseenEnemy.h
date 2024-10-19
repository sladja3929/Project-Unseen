// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UnseenCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Data/EnemyStateInfo.h"
#include "UnseenEnemy.generated.h"

DECLARE_MULTICAST_DELEGATE(FBackAttackedDelegate);

class UWidgetComponent;

UCLASS()
class UNSEEN_API AUnseenEnemy : public AUnseenCharacterBase
{
	GENERATED_BODY()

public:
	
	AUnseenEnemy();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State Info")
	TObjectPtr<UWidgetComponent> HeadStateIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State Info")
	TObjectPtr<UWidgetComponent> CombatGaugeTest;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BackArea;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void SetEnemyDetectionState(EEnemyDetectionState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyDetectionStateSet();
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StateInfo")
	FColor MaterialTintColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StateInfo")
	UTexture2D* Image = nullptr;
	
	FBackAttackedDelegate OnBackAttackEvent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WarningGauge = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GaugeUpSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GaugeDownDelay = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GaugeDownSpeed = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxWarningGauge = 100.f;
	
private:
	
	void SetEnemyDetectionInfoByState(EEnemyDetectionState NewState);

	UFUNCTION(BlueprintCallable)
	bool IsBackAttacked();
	
	UFUNCTION()
	void OnBackAttacked();
	
	UPROPERTY(VisibleAnywhere, Category="State")
	EEnemyDetectionState EnemyDetectionState = EEnemyDetectionState::Neutral;

	UPROPERTY(EditDefaultsOnly, Category="State")
	TObjectPtr<UEnemyStateInfo> EnemyStateInfo;

	UCapsuleComponent *CollisionComponent;
	bool IsBackAttack = false;
};
