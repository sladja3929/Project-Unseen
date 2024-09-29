// Unseen Project By 20240301


#include "AI/Service/BTService_IncreaseGauge.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_IncreaseGauge::UBTService_IncreaseGauge()
{
	NodeName = TEXT("Increase Gauge");
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_IncreaseGauge, BlackboardKey));
	BlackboardKey.SelectedKeyName = FName("CombatGauge");
	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UBTService_IncreaseGauge::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	float CurrentGauge = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());

	if(CurrentGauge + AmountToIncrease >= GaugeMaxLimit)
	{
		CurrentGauge = GaugeMaxLimit;
	}
	else
	{
		CurrentGauge += AmountToIncrease;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), CurrentGauge);
}

FString UBTService_IncreaseGauge::GetStaticDescription() const
{
	return FString::Printf(TEXT("Increase Gauge: %.1f/%.1fs <= %.1f"),
	AmountToIncrease, Interval, GaugeMaxLimit);
}
