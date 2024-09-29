// Unseen Project By 20240301


#include "AI/Service/BTService_RandomInteger.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_RandomInteger::UBTService_RandomInteger()
{
	NodeName = TEXT("Get Random Integer");
	BlackboardKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_RandomInteger, BlackboardKey));
	BlackboardKey.SelectedKeyName = FName("RandomInteger");

	Interval = 10000.f;
	RandomDeviation = 0.f;
	bCallTickOnSearchStart = true;
	bRestartTimerOnEachActivation = true;
}

void UBTService_RandomInteger::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	int32 RandomValue = FMath::RandRange(0, RandMax - 1);
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(BlackboardKey.SelectedKeyName, RandomValue);
}

FString UBTService_RandomInteger::GetStaticDescription() const
{
	return FString::Printf(TEXT("Get Random Int: 0 <= X < %d"), RandMax);
}
