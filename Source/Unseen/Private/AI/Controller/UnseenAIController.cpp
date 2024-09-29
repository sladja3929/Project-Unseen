// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/UnseenAIController.h"

#include "Actor/CriminalActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/UnseenCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

AUnseenAIController::AUnseenAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));

	SetPerceptionComponent(*AIPerception);

	// Set SightConfig
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// Set SightSense To AIPerception
	AIPerception->ConfigureSense(*SightConfig);

	// Set HearingConfig
	HearingConfig->HearingRange = AIHearingRadius;

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// Set HearingConfig To AIPerception
	AIPerception->ConfigureSense(*HearingConfig);

	// Set Delegate for OnTargetPerceptionUpdated
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AUnseenAIController::OnTargetDetected);
}

void AUnseenAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);
	}
}

void AUnseenAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (UAISense_Sight::StaticClass() == UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus))
	{
		UE_LOG(LogTemp, Display, TEXT("Sight Detection"));
		if (AUnseenCharacter* Player = Cast<AUnseenCharacter>(Actor))
		{
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Player);
		}
		
		if(ACriminalActor* NewCriminalActor = Cast<ACriminalActor>(Actor))
		{
			if(!IsValid(CriminalActor))
			{
				CriminalActor = NewCriminalActor;
				GetBlackboardComponent()->SetValueAsObject(TEXT("CriminalActor"), CriminalActor);
				GetBlackboardComponent()->ClearValue(TEXT("IsSearching"));
			}
			else if(CriminalActor->PriorityLevel < NewCriminalActor->PriorityLevel && !CriminalActor->bHasSearched)
			{
				// 현재 탐색 중인 범죄흔적 정찰 완료로 변경
				CriminalActor->bHasSearched = true;
				// 그 후 새로운 거로 고치기
				CriminalActor = NewCriminalActor;
				GetBlackboardComponent()->SetValueAsObject(TEXT("CriminalActor"), CriminalActor);
				GetBlackboardComponent()->ClearValue(TEXT("IsSearching"));
			}
			else
			{
				NewCriminalActor->bHasSearched = true;
			}
		}
	}
	if (UAISense_Hearing::StaticClass() == UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus))
	{
		UE_LOG(LogTemp, Display, TEXT("Hearing Detection"));
		if(FVector::Dist(HearingLocation, GetOwner()->GetActorLocation()) >=
			FVector::Dist(Stimulus.StimulusLocation, GetOwner()->GetActorLocation()))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("HearingLocation"), Stimulus.StimulusLocation);
		}
	}
}
