// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTService_UpdateTargetLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_UpdateTargetLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Target;
};
