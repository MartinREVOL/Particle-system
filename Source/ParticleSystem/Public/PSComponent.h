#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "HAL/CriticalSection.h"
#include "../PSParticleSystem.h"
#include "../PSSpawnSettings.h"
#include "PSComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class PARTICLESYSTEM_API UPSComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UPSComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//~ Begin UPrimitiveComponent Interface
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual bool ShouldRecreateProxyOnUpdateTransform() const override { return true; }
	virtual bool GetIgnoreBoundsForEditorFocus() const override { return true; }
	//~ End UPrimitiveComponent Interface

	//~ Begin USceneComponent Interface
	virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;
	//~ End USceneComponent Interface

	
private:
	mutable FCriticalSection RenderParticlesMutex;
	TArray<FPSParticle> RenderParticles;
	
public:
	// Expose particles to the scene proxy (render thread will read them)
	const TArray<FPSParticle>& GetParticles() const { return ParticleSystem.GetParticles(); }
	
	FVector GridSize = FVector(25, 25, 25);
	float GridSpacing = 10.0f;
	float ParticleSize = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PSComponent")
	float NbrParticules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PSComponent")
	int32 MaxParticles = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PSComponent")
	float SpawnRate = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ParticleSystem")
	FPSSpawnSettings SpawnSettings;

	FParticleSystem ParticleSystem;
};
