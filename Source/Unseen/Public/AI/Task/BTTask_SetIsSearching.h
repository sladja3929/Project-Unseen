// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetIsSearching.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTTask_SetIsSearching : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetIsSearching();
	
protected:
	UPROPERTY(EditAnywhere)
	bool bIsSearchingValue = true;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	virtual FString GetStaticDescription() const override;
};
