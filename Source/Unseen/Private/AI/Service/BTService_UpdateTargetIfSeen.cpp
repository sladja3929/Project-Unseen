// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_UpdateTargetIfSeen.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/UnseenCharacter.h"

UBTService_UpdateTargetIfSeen::UBTService_UpdateTargetIfSeen()
{
	NodeName = TEXT("Update Target Actor If Seen");
}

void UBTService_UpdateTargetIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AUnseenCharacter* TargetActor = Cast<AUnseenCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if(!TargetActor)
	{
		return;
	}
	
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if(!AIController)
	{
		return;
	}
	
	const AActor* OwnerActor = OwnerComp.GetOwner();
	if(!OwnerActor)
	{
		return;
	}
	
	const float Distance = FVector::Dist(OwnerComp.GetOwner()->GetActorLocation(), TargetActor->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(DistanceKey.SelectedKeyName, Distance);
	
	if(AIController->LineOfSightTo(TargetActor) && Distance <= RecognitionDistance)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), TargetActor);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
