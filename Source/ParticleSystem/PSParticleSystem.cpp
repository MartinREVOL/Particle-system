#include "PSParticleSystem.h"

void FParticleSystem::Init(int32 InMaxParticles, float InSpawnRate)
{
	MaxParticles = InMaxParticles;
	SpawnRate = InSpawnRate;

	Particles.Reserve(MaxParticles);
	SpawnAccumulator = 0.f;
}

void FParticleSystem::Tick(float DeltaTime,
						   const FTransform& ComponentToWorld,
						   const FPSSpawnSettings& SpawnSettings)
{
	// ------------------------
	// Update + Kill
	// ------------------------

	for (int32 i = Particles.Num() - 1; i >= 0; --i)
	{
		FPSParticle& P = Particles[i];

		P.Age += DeltaTime;

		if (!P.IsAlive())
		{
			Particles.RemoveAtSwap(i);
			continue;
		}

		P.Position += P.Velocity * DeltaTime;
	}

	// ------------------------
	// Spawn
	// ------------------------

	SpawnAccumulator += SpawnRate * DeltaTime;

	int32 ToSpawn = FMath::FloorToInt(SpawnAccumulator);
	SpawnAccumulator -= static_cast<float>(ToSpawn);

	ToSpawn = FMath::Min(ToSpawn, MaxParticles - Particles.Num());

	for (int32 s = 0; s < ToSpawn; ++s)
	{
		SpawnOne(ComponentToWorld, SpawnSettings);
	}
}

const TArray<FPSParticle>& FParticleSystem::GetParticles() const
{
	return Particles;
}


void FParticleSystem::SpawnOne(const FTransform& ComponentToWorld,
							   const FPSSpawnSettings& S)
{
	FPSParticle P;

	// Spawn position (random inside box)
	const FVector LocalOffset(
		FMath::FRandRange(-S.EmitterBoxExtent.X, S.EmitterBoxExtent.X),
		FMath::FRandRange(-S.EmitterBoxExtent.Y, S.EmitterBoxExtent.Y),
		FMath::FRandRange(-S.EmitterBoxExtent.Z, S.EmitterBoxExtent.Z)
	);

	P.Position = ComponentToWorld.TransformPosition(LocalOffset);

	// Direction + speed
	const FVector Dir = S.Direction.Sample();
	const float Speed = S.Speed.Sample();

	P.Velocity = Dir * Speed;

	// Lifetime
	P.Age = 0.f;
	P.Lifetime = S.Lifetime.Sample();

	// Color
	P.Color = S.Color.Sample();

	Particles.Add(MoveTemp(P));
}