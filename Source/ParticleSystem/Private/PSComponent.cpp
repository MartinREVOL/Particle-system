#include "ParticleSystem/Public/PSComponent.h"

#include "ParticleSystem/Public/PSPrimitiveSceneProxy.h"
#include "ParticleSystem/PSWorldSubsystem.h"

UPSComponent::UPSComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	NbrParticules = 25;
}

void UPSComponent::BeginPlay()
{
	Super::BeginPlay();

	GridSize.X = NbrParticules;
	GridSize.Y = NbrParticules;
	GridSize.Z = NbrParticules;

	if (UPSWorldSubsystem* Subsystem = GetPSWorldSubsystem())
	{
		SystemId = Subsystem->RequestSpawnSystem(GetComponentTransform(), SpawnSettings, MaxParticles, SpawnRate);
	}
}

void UPSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UPSWorldSubsystem* Subsystem = GetPSWorldSubsystem())
	{
		if (SystemId != INDEX_NONE)
		{
			Subsystem->RequestDestroySystem(SystemId);
			SystemId = INDEX_NONE;
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UPSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UPSWorldSubsystem* Subsystem = GetPSWorldSubsystem())
	{
		if (SystemId != INDEX_NONE)
		{
			Subsystem->UpdateSystemTransform(SystemId, GetComponentTransform());
		}
	}

	MarkRenderStateDirty();
}

FPrimitiveSceneProxy* UPSComponent::CreateSceneProxy()
{
	return new FPSPrimitiveSceneProxy(this);
}

FBoxSphereBounds UPSComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	const FVector Extent = SpawnSettings.EmitterBoxExtent + FVector(200.f);
	return FBoxSphereBounds(FBox(-Extent, Extent)).TransformBy(LocalToWorld);
}

UPSWorldSubsystem* UPSComponent::GetPSWorldSubsystem() const
{
	return GetWorld() ? GetWorld()->GetSubsystem<UPSWorldSubsystem>() : nullptr;
}

// const TArray<FPSParticle>* UPSComponent::GetParticles() const
// {
// 	if (const UPSWorldSubsystem* Subsystem = GetWorld() ? GetWorld()->GetSubsystem<UPSWorldSubsystem>() : nullptr)
// 	{
// 		if (const FParticleSystem* System = Subsystem->GetSystem(SystemId))
// 		{
// 			return &System->GetParticles();
// 		}
// 	}
//
// 	return nullptr;
// }

const TArray<FMovingParticle>* UPSComponent::GetParticles() const
{
	if (const UPSWorldSubsystem* Subsystem = GetWorld() ? GetWorld()->GetSubsystem<UPSWorldSubsystem>() : nullptr)
	{
		if (const FMovingParticleSystem* System = Subsystem->GetSystem(SystemId))
		{
			return &System->GetParticles();
		}
	}

	return nullptr;
}