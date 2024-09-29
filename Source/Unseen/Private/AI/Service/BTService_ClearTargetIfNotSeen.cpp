// Unseen Project By 20240301


#include "AI/Service/BTService_ClearTargetIfNotSeen.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/UnseenCharacter.h"

UBTService_ClearTargetIfNotSeen::UBTService_ClearTargetIfNotSeen()
{
	NodeName = TEXT("Clear TargetActor If Not Seen");
	BlackboardKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTService_ClearTargetIfNotSeen, BlackboardKey),
		AUnseenCharacter::StaticClass()
		);
	BlackboardKey.SelectedKeyName = FName("TargetActor");

	DistanceKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_ClearTargetIfNotSeen, DistanceKey));
	DistanceKey.SelectedKeyName = FName("Distance");

	Interval = 1.0f;
	RandomDeviation = 0.f;
}

void UBTService_ClearTargetIfNotSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	const APawn* AIPawn = AIController->GetPawn();
	if(!AIPawn)
	{
		return;
	}
	
	const float Distance = FVector::Dist(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(DistanceKey.SelectedKeyName, Distance);
	
	if(!AIController->LineOfSightTo(TargetActor) || Distance > RecognitionDistance)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}

FString UBTService_ClearTargetIfNotSeen::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}
