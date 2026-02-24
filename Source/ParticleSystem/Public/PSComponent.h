#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "PSComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
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
	// TODO : Implement FParticleSystem
	
public:
	// FParticleSystem* GetParticleSystem();
	FVector GridSize = FVector(25, 25, 25);
	float GridSpacing = 10.0f;
	float ParticleSize = 10.0f;
};
