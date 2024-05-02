// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/UnseenAIController.h"

void AUnseenAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}
}
