// Unseen Project By 20240301


#include "AI/Service/BTService_InitializeCombatGaugeIfLowerThanCurrent.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_InitializeCombatGaugeIfLowerThanCurrent::UBTService_InitializeCombatGaugeIfLowerThanCurrent()
{
	NodeName = TEXT("Initialize Combat Gauge If Lower Than Current");
	Interval = 10000.f;
	RandomDeviation = 0.f;
	
	bCallTickOnSearchStart = true;
	bRestartTimerOnEachActivation = true;
}

void UBTService_InitializeCombatGaugeIfLowerThanCurrent::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	float CurrentGauge = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), CurrentGauge >= GaugeAmount ? CurrentGauge : GaugeAmount);
}

FString UBTService_InitializeCombatGaugeIfLowerThanCurrent::GetStaticDescription() const
{
	return FString::Printf(TEXT("Initialize Gauge: %.0f"), GaugeAmount);
}
