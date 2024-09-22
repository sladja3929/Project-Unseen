// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AI\Task\BTTask_ClearBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	
	return EBTNodeResult::Succeeded;
}

FString UBTTask_ClearBlackboardValue::GetStaticDescription() const
{
	return FString::Printf(TEXT("Clear %s"), *GetSelectedBlackboardKey().ToString());
}
