// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_UpdatePlayerLocationOnce.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_UpdatePlayerLocationOnce::UBTTask_UpdatePlayerLocationOnce()
{
	NodeName = TEXT("Update Player Location Once Wherever The Player Is");
}

EBTNodeResult::Type UBTTask_UpdatePlayerLocationOnce::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(!PlayerPawn)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	return EBTNodeResult::Succeeded;
}
