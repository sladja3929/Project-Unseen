// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Data/EnemyStateInfo.h"
#include "BTTask_SetEnemyState.generated.h"

enum class EEnemyDetectionState : uint8;
/**
 * 
 */
UCLASS()
class UNSEEN_API UBTTask_SetEnemyState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetEnemyState();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual FString GetStaticDescription() const override;
public:
	UPROPERTY(EditAnywhere)
	EEnemyDetectionState EnemyDetectionState = EEnemyDetectionState::Neutral;
	
	FBlackboardKeySelector DetectionStateKey;
	

	
};
