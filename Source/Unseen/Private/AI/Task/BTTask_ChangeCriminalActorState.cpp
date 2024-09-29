// Unseen Project By 20240301


#include "AI/Task/BTTask_ChangeCriminalActorState.h"

#include "Actor/CriminalActor.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ChangeCriminalActorState::UBTTask_ChangeCriminalActorState()
{
	NodeName = TEXT("Change CriminalActor State");
	BlackboardKey.AddObjectFilter(
		this,
		GET_MEMBER_NAME_CHECKED(UBTTask_ChangeCriminalActorState, BlackboardKey),
		ACriminalActor::StaticClass()
		);
	BlackboardKey.SelectedKeyName = FName("CriminalActor");
}

EBTNodeResult::Type UBTTask_ChangeCriminalActorState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACriminalActor* CriminalActor = Cast<ACriminalActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

	if(!CriminalActor)
	{
		return EBTNodeResult::Failed;
	}
	
	CriminalActor->bHasSearched = bSearchStateValue;
	
	return EBTNodeResult::Succeeded;
}

FString UBTTask_ChangeCriminalActorState::GetStaticDescription() const
{
	if(bSearchStateValue)
	{
		return FString::Printf(TEXT("Change Criminal Actor`s bHasSearched to true"));
	}
	return FString::Printf(TEXT("Change Criminal Actor`s bHasSearched to false"));
}
