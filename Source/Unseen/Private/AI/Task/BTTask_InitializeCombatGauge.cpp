// Unseen Project By 20240301


#include "AI/Task/BTTask_InitializeCombatGauge.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_InitializeCombatGauge::UBTTask_InitializeCombatGauge()
{
	NodeName = TEXT("Initialize Combat Gauge");
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_InitializeCombatGauge, BlackboardKey));
	BlackboardKey.SelectedKeyName = FName("CombatGauge");
}

EBTNodeResult::Type UBTTask_InitializeCombatGauge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Display, TEXT("Init Combat Gauge"));
	
	if(OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey()) < GaugeAmount)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), GaugeAmount);
	}

	return EBTNodeResult::Succeeded;
}

FString UBTTask_InitializeCombatGauge::GetStaticDescription() const
{
	return FString::Printf(TEXT("Initialize Combat Gauge: %.0f"), GaugeAmount);
}
