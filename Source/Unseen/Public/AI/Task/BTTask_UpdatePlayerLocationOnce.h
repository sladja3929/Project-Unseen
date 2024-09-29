// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_UpdatePlayerLocationOnce.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTTask_UpdatePlayerLocationOnce : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_UpdatePlayerLocationOnce();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
