// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RandomInteger.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTService_RandomInteger : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_RandomInteger();

	UPROPERTY(EditAnywhere)
	int32 RandMax = 2;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	virtual FString GetStaticDescription() const override;
	
};
