// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "UnseenAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API UUnseenAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UUnseenAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
