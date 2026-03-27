#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "ParticleSystem/PSSpawnSettings.h"
#include "PSComponent.generated.h"

class FPSPrimitiveSceneProxy;
class UPSWorldSubsystem;
struct FPSParticle;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PARTICLESYSTEM_API UPSComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UPSComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual bool ShouldRecreateProxyOnUpdateTransform() const override { return true; }
	virtual bool GetIgnoreBoundsForEditorFocus() const override { return true; }

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

	const TArray<FPSParticle>* GetParticles() const;

public:
	FVector GridSize = FVector(25, 25, 25);
	float GridSpacing = 10.0f;
	float ParticleSize = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PSComponent")
	float NbrParticules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PSComponent")
	int32 MaxParticles = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PSComponent")
	float SpawnRate = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PSComponent")
	FPSSpawnSettings SpawnSettings;

private:
	int32 SystemId = INDEX_NONE;

	UPSWorldSubsystem* GetPSWorldSubsystem() const;
};