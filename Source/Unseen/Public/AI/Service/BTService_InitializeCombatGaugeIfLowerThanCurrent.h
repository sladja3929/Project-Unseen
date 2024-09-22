// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_InitializeCombatGaugeIfLowerThanCurrent.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTService_InitializeCombatGaugeIfLowerThanCurrent : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_InitializeCombatGaugeIfLowerThanCurrent();
	
	UPROPERTY(EditAnywhere)
	float GaugeAmount = 100.f;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	virtual FString GetStaticDescription() const override;

};
