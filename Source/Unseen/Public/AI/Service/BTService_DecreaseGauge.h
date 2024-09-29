// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DecreaseGauge.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTService_DecreaseGauge : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_DecreaseGauge();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	virtual FString GetStaticDescription() const override;
	
public:
	UPROPERTY(EditAnywhere)
	float AmountToDecrease = 1.f;

	UPROPERTY(EditAnywhere)
	float GaugeMinLimit = 50.f;
	
};
