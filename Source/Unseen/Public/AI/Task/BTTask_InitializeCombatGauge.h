// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_InitializeCombatGauge.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTTask_InitializeCombatGauge : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_InitializeCombatGauge();

	UPROPERTY(EditAnywhere)
	float GaugeAmount = 100;
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	virtual FString GetStaticDescription() const override;
};
