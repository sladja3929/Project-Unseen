// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IncreaseGauge.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTService_IncreaseGauge : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_IncreaseGauge();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	virtual FString GetStaticDescription() const override;
public:
	UPROPERTY(EditAnywhere)
	float AmountToIncrease = 1.f;

	UPROPERTY(EditAnywhere)
	float GaugeMaxLimit = 100.f;
};
