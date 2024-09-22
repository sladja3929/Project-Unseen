// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UnseenAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FBackAttackEndDelegate);

UCLASS()
class UNSEEN_API UUnseenAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	FBackAttackEndDelegate OnBackAttackEnd;
	
private:
	UFUNCTION()
	void AnimNotify_BackAttackEnd();
};
