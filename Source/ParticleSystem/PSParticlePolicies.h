#pragma once

#include "CoreMinimal.h"
#include "PSSpawnSettings.h"
#include "PSParticles.h"

struct FPSBasicParticleUpdatePolicy
{
	static void Update(FPSBasicParticle& Particle, float DeltaTime)
	{
		Particle.Age += DeltaTime;
	}
};

struct FPSMovingParticleUpdatePolicy
{
	static void Update(FPSMovingParticle& Particle, float DeltaTime)
	{
		Particle.Age += DeltaTime;
		Particle.Position += Particle.Velocity * DeltaTime;
	}
};

struct FPSBasicParticleSpawnPolicy
{
	static void Spawn(FPSBasicParticle& Particle, const FTransform& Transform, const FPSSpawnSettings& Settings)
	{
		const FVector LocalOffset(
			FMath::FRandRange(-Settings.EmitterBoxExtent.X, Settings.EmitterBoxExtent.X),
			FMath::FRandRange(-Settings.EmitterBoxExtent.Y, Settings.EmitterBoxExtent.Y),
			FMath::FRandRange(-Settings.EmitterBoxExtent.Z, Settings.EmitterBoxExtent.Z)
		);

		Particle.Position = Transform.TransformPosition(LocalOffset);
		Particle.Age = 0.f;
		Particle.Lifetime = Settings.Lifetime.Sample();
		Particle.Color = Settings.Color.Sample();
	}
};

struct FPSMovingParticleSpawnPolicy
{
	static void Spawn(FPSMovingParticle& Particle, const FTransform& Transform, const FPSSpawnSettings& Settings)
	{
		const FVector LocalOffset(
			FMath::FRandRange(-Settings.EmitterBoxExtent.X, Settings.EmitterBoxExtent.X),
			FMath::FRandRange(-Settings.EmitterBoxExtent.Y, Settings.EmitterBoxExtent.Y),
			FMath::FRandRange(-Settings.EmitterBoxExtent.Z, Settings.EmitterBoxExtent.Z)
		);

		Particle.Position = Transform.TransformPosition(LocalOffset);

		const FVector Dir = Settings.Direction.Sample();
		const float Speed = Settings.Speed.Sample();
		Particle.Velocity = Dir * Speed;

		Particle.Age = 0.f;
		Particle.Lifetime = Settings.Lifetime.Sample();
		Particle.Color = Settings.Color.Sample();
	}
};