#pragma once

#include "CoreMinimal.h"
#include "PSSpawnSettings.h"


struct FPSParticle
{
	FVector Position = FVector::ZeroVector;
	FVector Velocity = FVector::ZeroVector;
	float Age = 0.f;
	float Lifetime = 2.f;
	FLinearColor Color = FLinearColor::Green;

	bool IsAlive() const { return Age < Lifetime; }
};


class FParticleSystem
{
public:

	void Init(int32 InMaxParticles, float InSpawnRate);

	void Tick(float DeltaTime, const FTransform& ComponentToWorld, const FPSSpawnSettings& SpawnSettings);

	const TArray<FPSParticle>& GetParticles() const;

private:

	void SpawnOne(const FTransform& ComponentToWorld,
				  const FPSSpawnSettings& SpawnSettings);

private:

	TArray<FPSParticle> Particles;

	int32 MaxParticles = 2000;
	float SpawnRate = 300.f;
	float SpawnAccumulator = 0.f;
};