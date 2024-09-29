// Unseen Project By 20240301


#include "AI/Decorator/BTDecorator_CheckActorTag.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckActorTag::UBTDecorator_CheckActorTag()
{
	NodeName = TEXT("Check Actor Tag");
}

bool UBTDecorator_CheckActorTag::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	
	if (!IsValid(TargetActor))
	{
		return false;
	}
	
	return TargetActor->ActorHasTag(TagName);
}

FString UBTDecorator_CheckActorTag::GetStaticDescription() const
{
	return FString::Printf(TEXT("Check %s Has <%s> Tag"), *GetSelectedBlackboardKey().ToString(), *TagName.ToString());
}
