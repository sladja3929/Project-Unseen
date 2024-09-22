// Unseen Project By 20240301

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CriminalActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNSEEN_API ACriminalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACriminalActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PriorityLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasSearched = false;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
};
