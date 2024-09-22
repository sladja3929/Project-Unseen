// Unseen Project By 20240301


#include "AI/Task/BTTask_SetEnemyState.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/UnseenEnemy.h"

UBTTask_SetEnemyState::UBTTask_SetEnemyState()
{
	NodeName = "Set Enemy State";

	DetectionStateKey.AddEnumFilter(this,
		GET_MEMBER_NAME_CHECKED(UBTTask_SetEnemyState, DetectionStateKey),
		StaticEnum<EEnemyDetectionState>()
		);
	DetectionStateKey.SelectedKeyName = FName("DetectionState");
}

EBTNodeResult::Type UBTTask_SetEnemyState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AUnseenEnemy* Enemy = Cast<AUnseenEnemy>(AIController->GetPawn());
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(DetectionStateKey.SelectedKeyName, static_cast<uint8>(EnemyDetectionState));
	Enemy->SetEnemyDetectionState(EnemyDetectionState);

	return EBTNodeResult::Succeeded;
}

FString UBTTask_SetEnemyState::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(),
						   *StaticEnum<EEnemyDetectionState>()->GetNameStringByValue(
							   static_cast<int64>(EnemyDetectionState))
	);
}