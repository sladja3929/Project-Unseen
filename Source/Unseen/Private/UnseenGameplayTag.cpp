// Unseen Project By 20240301


#include "UnseenGameplayTag.h"
#include "GameplayTagsManager.h"

FUnseenGameplayTags FUnseenGameplayTags::GameplayTags;

void FUnseenGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.CriminalActor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CriminalActor"),
		FString("Enemy Found CriminalActor")
	);
	GameplayTags.CriminalBehavior = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("CriminalBehavior"),
		FString("Player do CriminalBehavior")
	);
	GameplayTags.ForbiddenArea = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("ForbiddenArea"),
		FString("Player is in ForbiddenArea")
	);
}
