// Unseen Project By 20240301


#include "UnseenAssetManager.h"

#include "UnseenGameplayTag.h"

UUnseenAssetManager& UUnseenAssetManager::Get()
{
	check(GEngine);

	UUnseenAssetManager* UnseenAssetManager = Cast<UUnseenAssetManager>(GEngine->AssetManager);
	return *UnseenAssetManager;
}


void UUnseenAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FUnseenGameplayTags::InitializeNativeGameplayTags();

}
