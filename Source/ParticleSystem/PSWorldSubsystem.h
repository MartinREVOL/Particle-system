#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PSParticleSystem.h"
#include "PSSpawnSettings.h"
#include "PSWorldSubsystem.generated.h"

USTRUCT()
struct FPSSystemEntry
{
	GENERATED_BODY()

	int32 Id = INDEX_NONE;
	FParticleSystem System;
	FTransform Transform = FTransform::Identity;
	FPSSpawnSettings SpawnSettings;
	bool bPendingDestroy = false;
};

UCLASS()
class PARTICLESYSTEM_API UPSWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override { return true; }

	int32 RequestSpawnSystem(const FTransform& InTransform, const FPSSpawnSettings& InSpawnSettings, int32 MaxParticles, float SpawnRate);
	void RequestDestroySystem(int32 SystemId);

	void UpdateSystemTransform(int32 SystemId, const FTransform& NewTransform);

	const FParticleSystem* GetSystem(int32 SystemId) const;

private:
	FPSSystemEntry* FindEntry(int32 SystemId);
	const FPSSystemEntry* FindEntry(int32 SystemId) const;

	void ProcessPendingDestroy();

private:
	UPROPERTY(Transient)
	TArray<FPSSystemEntry> Systems;

	int32 NextSystemId = 0;
};