// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "UnseenAIController.generated.h"

class ACriminalActor;
/**
 * 
 */
UCLASS()
class UNSEEN_API AUnseenAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AUnseenAIController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> AIPerception;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehaviorTree;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* NeutralIdleBehaviorTree;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AwakeIdleBehaviorTree;

	UPROPERTY(EditAnywhere, Category="ShooterAIController|SightConfig")
	class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere, Category="ShooterAIController|SightConfig")
	float AISightRadius = 1000.f;
	UPROPERTY(EditAnywhere, Category="ShooterAIController|SightConfig")
	float AILoseSightRadius = 1000.f;
	UPROPERTY(EditAnywhere, Category="ShooterAIController|SightConfig")
	float AIFieldOfView = 45.f;
	UPROPERTY(EditAnywhere, Category="ShooterAIController|SightConfig")
	float AISightAge = 500.f;
	UPROPERTY(EditAnywhere, Category="ShooterAIController|SightConfig")
	float AILastSeenLocation = 100.f;

	
	UPROPERTY(EditAnywhere, Category="ShooterAIController|HearingConfig")
	class UAISenseConfig_Hearing* HearingConfig;
	UPROPERTY(EditAnywhere, Category="ShooterAIController|HearingConfig")
	float AIHearingRadius = 2000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TObjectPtr<ACriminalActor> CriminalActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	FVector HearingLocation;
	
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);
	
};
