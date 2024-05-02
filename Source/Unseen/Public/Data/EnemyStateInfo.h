// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyStateInfo.generated.h"

USTRUCT(BlueprintType)
struct FEnemyDetectionStateInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FColor Color = FColor::Transparent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed = 0;
};

UENUM(BlueprintType)
enum class EEnemyDetectionState : uint8
{
	Neutral,
	SmallDetection,
	IndirectDetection,
	DirectDetection,
	Combat
};

UCLASS()
class UNSEEN_API UEnemyStateInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FEnemyDetectionStateInfo* FindEnemyDetectionStateInfo(EEnemyDetectionState NewState);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EEnemyDetectionState, FEnemyDetectionStateInfo> EnemyDetectionStateInformation;
};
