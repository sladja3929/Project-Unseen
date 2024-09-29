// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_UpdateTargetLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/UnseenCharacter.h"

UBTService_UpdateTargetLocation::UBTService_UpdateTargetLocation()
{
	NodeName = TEXT("Update Target Location");
	Target.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_UpdateTargetLocation, Target),
		AUnseenCharacter::StaticClass()
		);
	Target.SelectedKeyName = FName("TargetActor");
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateTargetLocation, BlackboardKey));
	BlackboardKey.SelectedKeyName = FName("LastKnownTargetLocation");

	Interval = 1.f;
	RandomDeviation = 0.f;
}

void UBTService_UpdateTargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AUnseenCharacter* TargetActor = Cast<AUnseenCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	if(!TargetActor)
	{
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(this);
	if(!NavSystem)
	{
		return;
	}

	FVector Origin = TargetActor->GetActorLocation();
	FNavLocation NavLocation;
	float Radius = 50.f;
	
	while (!NavSystem->GetRandomReachablePointInRadius(Origin, Radius, NavLocation))
	{
		Radius += 50.f;
		if(Radius > 500)
		{
			return;
		}
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
}
