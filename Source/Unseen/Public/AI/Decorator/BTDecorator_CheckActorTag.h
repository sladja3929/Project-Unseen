// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckActorTag.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UBTDecorator_CheckActorTag : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckActorTag();

	UPROPERTY(EditAnywhere)
	FName TagName = "";

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	virtual FString GetStaticDescription() const override;
};
