// Unseen Project By 20240301


#include "Actor/CriminalActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ACriminalActor::ACriminalActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Mesh->SetSimulatePhysics(true);
}

