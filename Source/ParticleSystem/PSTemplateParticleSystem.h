#pragma once

#include "CoreMinimal.h"

template<typename TParticle, typename TUpdatePolicy, typename TSpawnPolicy>
class TParticleSystem
{
public:
	void Init(int32 InMaxParticles, float InSpawnRate)
	{
		MaxParticles = InMaxParticles;
		SpawnRate = InSpawnRate;
		Particles.Reserve(MaxParticles);
		SpawnAccumulator = 0.f;
	}

	template<typename TSpawnContext>
	void Tick(float DeltaTime, const TSpawnContext& SpawnContext)
	{
		// Update + compact
		int32 WriteIndex = 0;
		const int32 Count = Particles.Num();

		for (int32 ReadIndex = 0; ReadIndex < Count; ++ReadIndex)
		{
			TParticle& P = Particles[ReadIndex];

			TUpdatePolicy::Update(P, DeltaTime);

			if (!TUpdatePolicy::IsAlive(P))
			{
				continue;
			}

			if (WriteIndex != ReadIndex)
			{
				Particles[WriteIndex] = MoveTemp(P);
			}

			++WriteIndex;
		}

		Particles.SetNum(WriteIndex, EAllowShrinking::No);

		// Spawn
		SpawnAccumulator += SpawnRate * DeltaTime;

		int32 ToSpawn = FMath::FloorToInt(SpawnAccumulator);
		SpawnAccumulator -= static_cast<float>(ToSpawn);

		ToSpawn = FMath::Min(ToSpawn, MaxParticles - Particles.Num());

		for (int32 s = 0; s < ToSpawn; ++s)
		{
			TParticle NewParticle;
			TSpawnPolicy::Spawn(NewParticle, SpawnContext);
			Particles.Add(MoveTemp(NewParticle));
		}
	}

	const TArray<TParticle>& GetParticles() const
	{
		return Particles;
	}

private:
	TArray<TParticle> Particles;
	int32 MaxParticles = 2000;
	float SpawnRate = 300.f;
	float SpawnAccumulator = 0.f;
};