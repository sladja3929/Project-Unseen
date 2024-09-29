// Unseen Project By 20240301


#include "AI/Service/BTService_DecreaseGauge.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_DecreaseGauge::UBTService_DecreaseGauge()
{
	NodeName = TEXT("Decrease Gauge");
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_DecreaseGauge, BlackboardKey));
	BlackboardKey.SelectedKeyName = FName("CombatGauge");
	Interval = 1.0f;
	RandomDeviation = 0.0f;
}

void UBTService_DecreaseGauge::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	float CurrentGauge = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	
	if(CurrentGauge >= GaugeMinLimit && CurrentGauge - AmountToDecrease <= GaugeMinLimit)
	{
		CurrentGauge = GaugeMinLimit;
	}
	else if(CurrentGauge >= GaugeMinLimit)
	{
		CurrentGauge -= AmountToDecrease;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), CurrentGauge);
}

FString UBTService_DecreaseGauge::GetStaticDescription() const
{
	return FString::Printf(TEXT("Decrease Gauge: -%.1f/%.1fs >= %.1f"),
		AmountToDecrease, Interval, GaugeMinLimit);
}
