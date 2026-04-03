#pragma once

#include "CoreMinimal.h"
#include "PSParticleTypes.h"
#include "PSSpawnSettings.h"

struct FPSSpawnContext
{
	FTransform ComponentTransform = FTransform::Identity;
	FPSSpawnSettings SpawnSettings;
};

// =========================
// Update Policies
// =========================

struct FMovingParticleUpdatePolicy
{
	static void Update(FMovingParticle& Particle, float DeltaTime)
	{
		Particle.Age += DeltaTime;
		Particle.Position += Particle.Velocity * DeltaTime;
	}

	static bool IsAlive(const FMovingParticle& Particle)
	{
		return Particle.Age < Particle.Lifetime;
	}
};

struct FStaticParticleUpdatePolicy
{
	static void Update(FStaticParticle& Particle, float DeltaTime)
	{
		Particle.Age += DeltaTime;
	}

	static bool IsAlive(const FStaticParticle& Particle)
	{
		return Particle.Age < Particle.Lifetime;
	}
};

// =========================
// Spawn Policies
// =========================

struct FMovingParticleSpawnPolicy
{
	static void Spawn(FMovingParticle& Particle, const FPSSpawnContext& Context)
	{
		const FPSSpawnSettings& S = Context.SpawnSettings;

		const FVector LocalOffset(
			FMath::FRandRange(-S.EmitterBoxExtent.X, S.EmitterBoxExtent.X),
			FMath::FRandRange(-S.EmitterBoxExtent.Y, S.EmitterBoxExtent.Y),
			FMath::FRandRange(-S.EmitterBoxExtent.Z, S.EmitterBoxExtent.Z)
		);

		Particle.Position = Context.ComponentTransform.TransformPosition(LocalOffset);

		const FVector Dir = S.Direction.Sample();
		const float Speed = S.Speed.Sample();

		Particle.Velocity = Dir * Speed;
		Particle.Age = 0.f;
		Particle.Lifetime = S.Lifetime.Sample();
		Particle.Color = S.Color.Sample();
	}
};

struct FStaticParticleSpawnPolicy
{
	static void Spawn(FStaticParticle& Particle, const FPSSpawnContext& Context)
	{
		const FPSSpawnSettings& S = Context.SpawnSettings;

		const FVector LocalOffset(
			FMath::FRandRange(-S.EmitterBoxExtent.X, S.EmitterBoxExtent.X),
			FMath::FRandRange(-S.EmitterBoxExtent.Y, S.EmitterBoxExtent.Y),
			FMath::FRandRange(-S.EmitterBoxExtent.Z, S.EmitterBoxExtent.Z)
		);

		Particle.Position = Context.ComponentTransform.TransformPosition(LocalOffset);
		Particle.Age = 0.f;
		Particle.Lifetime = S.Lifetime.Sample();
		Particle.Color = S.Color.Sample();
	}
};