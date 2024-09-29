// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
struct FUnseenGameplayTags
{
public:
	static const FUnseenGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag CriminalActor;
	FGameplayTag CriminalBehavior;

	FGameplayTag ForbiddenArea;

protected:

private:
	static FUnseenGameplayTags GameplayTags;
};
