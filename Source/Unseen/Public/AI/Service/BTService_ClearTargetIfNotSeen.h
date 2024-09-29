// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ClearTargetIfNotSeen.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTService_ClearTargetIfNotSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ClearTargetIfNotSeen();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RecognitionDistance = 2000.f;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	virtual FString GetStaticDescription() const override;

	UPROPERTY(VisibleAnywhere)
	FBlackboardKeySelector DistanceKey;
};
