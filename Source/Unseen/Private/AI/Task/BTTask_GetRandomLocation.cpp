// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_GetRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	NodeName = TEXT("Get Random Location");
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	const AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	if(!AIController)
	{
		return EBTNodeResult::Failed;
	}

	const APawn* Pawn = AIController->GetPawn();
	if(!Pawn)
	{
		return EBTNodeResult::Failed;
	}
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(this);
	if(!NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	const FVector OriginLocation = Pawn->GetActorLocation();
	FNavLocation PatrolLocation;

	if(NavSystem->GetRandomReachablePointInRadius(OriginLocation, Radius, PatrolLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PatrolLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
