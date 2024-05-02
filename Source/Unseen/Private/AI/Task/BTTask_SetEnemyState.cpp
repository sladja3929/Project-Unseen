// Unseen Project By 20240301


#include "AI/Task/BTTask_SetEnemyState.h"

#include "AIController.h"
#include "Character/UnseenEnemy.h"

UBTTask_SetEnemyState::UBTTask_SetEnemyState()
{
	NodeName = "Set Enemy State";
}

FString UBTTask_SetEnemyState::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(),
	                       *StaticEnum<EEnemyDetectionState>()->GetNameStringByValue(
		                       static_cast<int64>(EnemyDetectionState))
	);
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

	Enemy->SetEnemyDetectionState(EnemyDetectionState);
	return EBTNodeResult::Succeeded;
}
