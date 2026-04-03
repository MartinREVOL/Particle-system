#include "PSWorldSubsystem.h"
#include "PSParticlePolicies.h"

void UPSWorldSubsystem::Tick(float DeltaTime)
{
	for (FPSMovingSystemEntry& Entry : Systems)
	{
		if (Entry.bPendingDestroy)
		{
			continue;
		}

		FPSSpawnContext SpawnContext;
		SpawnContext.ComponentTransform = Entry.Transform;
		SpawnContext.SpawnSettings = Entry.SpawnSettings;

		Entry.System.Tick(DeltaTime, SpawnContext);
	}

	ProcessPendingDestroy();
}

TStatId UPSWorldSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UPSWorldSubsystem, STATGROUP_Tickables);
}

int32 UPSWorldSubsystem::RequestSpawnSystem(
	const FTransform& InTransform,
	const FPSSpawnSettings& InSpawnSettings,
	int32 MaxParticles,
	float SpawnRate)
{
	FPSMovingSystemEntry NewEntry;
	NewEntry.Id = NextSystemId++;
	NewEntry.Transform = InTransform;
	NewEntry.SpawnSettings = InSpawnSettings;
	NewEntry.bPendingDestroy = false;
	NewEntry.System.Init(MaxParticles, SpawnRate);

	Systems.Add(MoveTemp(NewEntry));

	return Systems.Last().Id;
}

void UPSWorldSubsystem::RequestDestroySystem(int32 SystemId)
{
	if (FPSMovingSystemEntry* Entry = FindEntry(SystemId))
	{
		Entry->bPendingDestroy = true;
	}
}

void UPSWorldSubsystem::UpdateSystemTransform(int32 SystemId, const FTransform& NewTransform)
{
	if (FPSMovingSystemEntry* Entry = FindEntry(SystemId))
	{
		Entry->Transform = NewTransform;
	}
}

const FMovingParticleSystem* UPSWorldSubsystem::GetSystem(int32 SystemId) const
{
	if (const FPSMovingSystemEntry* Entry = FindEntry(SystemId))
	{
		if (!Entry->bPendingDestroy)
		{
			return &Entry->System;
		}
	}

	return nullptr;
}

FPSMovingSystemEntry* UPSWorldSubsystem::FindEntry(int32 SystemId)
{
	return Systems.FindByPredicate([SystemId](const FPSMovingSystemEntry& Entry)
	{
		return Entry.Id == SystemId;
	});
}

const FPSMovingSystemEntry* UPSWorldSubsystem::FindEntry(int32 SystemId) const
{
	return Systems.FindByPredicate([SystemId](const FPSMovingSystemEntry& Entry)
	{
		return Entry.Id == SystemId;
	});
}

void UPSWorldSubsystem::ProcessPendingDestroy()
{
	for (int32 i = Systems.Num() - 1; i >= 0; --i)
	{
		if (Systems[i].bPendingDestroy)
		{
			Systems.RemoveAtSwap(i);
		}
	}
}