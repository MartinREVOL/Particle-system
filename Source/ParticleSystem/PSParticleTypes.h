#pragma once

#include "CoreMinimal.h"

struct FMovingParticle
{
	FVector Position = FVector::ZeroVector;
	FVector Velocity = FVector::ZeroVector;
	float Age = 0.f;
	float Lifetime = 2.f;
	FLinearColor Color = FLinearColor::Green;
};

struct FStaticParticle
{
	FVector Position = FVector::ZeroVector;
	float Age = 0.f;
	float Lifetime = 2.f;
	FLinearColor Color = FLinearColor::Green;
};