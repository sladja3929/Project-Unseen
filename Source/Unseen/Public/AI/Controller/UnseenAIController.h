// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnseenAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNSEEN_API AUnseenAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
};
