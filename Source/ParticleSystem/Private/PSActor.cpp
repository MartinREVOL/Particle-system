#include "ParticleSystem/Public/PSActor.h"

#include "ParticleSystem/Public/PSComponent.h"


APSActor::APSActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	PSComponent = CreateDefaultSubobject<UPSComponent>("PSComponent");
	PSComponent->Mobility = EComponentMobility::Movable;

	RootComponent = PSComponent;
}

