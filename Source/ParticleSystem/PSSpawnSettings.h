#pragma once
#include "CoreMinimal.h"
#include "PSSpawnSettings.generated.h"

// Float param: either fixed or random range
USTRUCT(BlueprintType)
struct FPSFloatParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param")
	bool bRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param", meta=(EditCondition="!bRandom"))
	float Value = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param", meta=(EditCondition="bRandom"))
	float Min = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param", meta=(EditCondition="bRandom"))
	float Max = 1.f;

	float Sample() const
	{
		return bRandom ? FMath::FRandRange(Min, Max) : Value;
	}
};

// Color param: fixed or random between two colors
USTRUCT(BlueprintType)
struct FPSColorParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param")
	bool bRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param", meta=(EditCondition="!bRandom"))
	FLinearColor Value = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param", meta=(EditCondition="bRandom"))
	FLinearColor Min = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param", meta=(EditCondition="bRandom"))
	FLinearColor Max = FLinearColor::Green;

	FLinearColor Sample() const
	{
		if (!bRandom) return Value;
		return FLinearColor(
			FMath::FRandRange(Min.R, Max.R),
			FMath::FRandRange(Min.G, Max.G),
			FMath::FRandRange(Min.B, Max.B),
			FMath::FRandRange(Min.A, Max.A)
		);
	}
};

// Direction param: either fixed dir or random cone around it
USTRUCT(BlueprintType)
struct FPSDirectionParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param")
	bool bRandom = true;

	// Used when !bRandom (or as the cone axis when random)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param")
	FVector Direction = FVector::UpVector;

	// Used when bRandom: random direction inside a cone around Direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Param", meta=(ClampMin="0.0", ClampMax="180.0", EditCondition="bRandom"))
	float ConeHalfAngleDegrees = 45.f;

	FVector Sample() const
	{
		const FVector Axis = Direction.GetSafeNormal();
		if (!bRandom)
		{
			return Axis.IsNearlyZero() ? FVector::UpVector : Axis;
		}

		// Random unit vector in cone
		const float HalfAngleRad = FMath::DegreesToRadians(ConeHalfAngleDegrees);
		const float CosMin = FMath::Cos(HalfAngleRad);

		const float Z = FMath::FRandRange(CosMin, 1.f);
		const float Phi = FMath::FRandRange(0.f, 2.f * PI);
		const float SinT = FMath::Sqrt(1.f - Z * Z);

		// Local cone vector around +Z
		FVector Local(SinT * FMath::Cos(Phi), SinT * FMath::Sin(Phi), Z);

		// Rotate local +Z axis to Axis
		const FQuat Rot = FQuat::FindBetweenNormals(FVector::UpVector, Axis.IsNearlyZero() ? FVector::UpVector : Axis);
		return Rot.RotateVector(Local).GetSafeNormal();
	}
};

USTRUCT(BlueprintType)
struct FPSSpawnSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FPSFloatParam Lifetime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FPSFloatParam Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FPSColorParam Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FPSDirectionParam Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	FVector EmitterBoxExtent = FVector(50,50,50);
};