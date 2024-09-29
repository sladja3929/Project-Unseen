// Unseen Project By 20240301


#include "AI/Task/BTTask_SetIsSearching.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetIsSearching::UBTTask_SetIsSearching()
{
	NodeName = TEXT("Set Is Searching");
	BlackboardKey.AddBoolFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_SetIsSearching, BlackboardKey));
	BlackboardKey.SelectedKeyName = FName("IsSearching");
}

EBTNodeResult::Type UBTTask_SetIsSearching::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bIsSearchingValue);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

FString UBTTask_SetIsSearching::GetStaticDescription() const
{
	return FString::Printf(TEXT("Set Is Searching: %s"), bIsSearchingValue ? TEXT("true") : TEXT("false"));
}
