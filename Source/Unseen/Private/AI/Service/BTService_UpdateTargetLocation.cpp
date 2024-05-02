// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_UpdateTargetLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/UnseenCharacter.h"

UBTService_UpdateTargetLocation::UBTService_UpdateTargetLocation()
{
	NodeName = TEXT("Update Target Location");
}

void UBTService_UpdateTargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AUnseenCharacter* TargetActor = Cast<AUnseenCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	if(!TargetActor)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetActor->GetActorLocation());
}
