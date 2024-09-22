// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/UnseenCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Data/EnemyStateInfo.h"
#include "UnseenEnemy.generated.h"


UCLASS()
class UNSEEN_API AUnseenEnemy : public AUnseenCharacterBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetEnemyDetectionState(EEnemyDetectionState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyDetectionStateSet();
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StateInfoTest")
	FColor MaterialTintColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StateInfoTest")
	UTexture2D* Image = nullptr;

	
protected:
	virtual void BeginPlay() override;
	
private:
	void SetEnemyDetectionInfoByState(EEnemyDetectionState NewState);
	
	UPROPERTY(VisibleAnywhere, Category="State")
	EEnemyDetectionState EnemyDetectionState = EEnemyDetectionState::Neutral;

	UPROPERTY(EditDefaultsOnly, Category="State")
	TObjectPtr<UEnemyStateInfo> EnemyStateInfo;

	UBoxComponent* BackArea;

};
