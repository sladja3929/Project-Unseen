// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateTargetIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTService_UpdateTargetIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_UpdateTargetIfSeen();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	float RecognitionDistance = 2000.f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector DistanceKey;
};
