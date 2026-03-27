#pragma once

#include "CoreMinimal.h"

struct FPSBasicParticle
{
	FVector Position = FVector::ZeroVector;
	float Age = 0.f;
	float Lifetime = 2.f;
	FLinearColor Color = FLinearColor::Green;

	bool IsAlive() const
	{
		return Age < Lifetime;
	}
};

struct FPSMovingParticle
{
	FVector Position = FVector::ZeroVector;
	FVector Velocity = FVector::ZeroVector;
	float Age = 0.f;
	float Lifetime = 2.f;
	FLinearColor Color = FLinearColor::Green;

	bool IsAlive() const
	{
		return Age < Lifetime;
	}
};