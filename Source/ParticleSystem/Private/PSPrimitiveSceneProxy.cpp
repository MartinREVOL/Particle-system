#include "PSPrimitiveSceneProxy.h"

FPSPrimitiveSceneProxy::FPSPrimitiveSceneProxy(const UPSComponent* InComponent) 
	: FPrimitiveSceneProxy(InComponent)
	, Component(InComponent)
{
}

FPSPrimitiveSceneProxy::~FPSPrimitiveSceneProxy()
{
}

FPrimitiveViewRelevance FPSPrimitiveSceneProxy::GetViewRelevance(const FSceneView* View) const
{
	FPrimitiveViewRelevance Result;
	
	const UWorld* World = GetScene().GetWorld();
	if (!World || !World->IsGameWorld())
	{
		return Result;
	}
	
	Result.bDrawRelevance = IsShown(View);
	Result.bDynamicRelevance = true;
	Result.bSeparateTranslucency = Result.bNormalTranslucency = IsShown(View);
	Result.bShadowRelevance = false;
	Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
	return Result;
}

void FPSPrimitiveSceneProxy::GetDynamicMeshElements(
	const TArray<const FSceneView*>& Views,
	const FSceneViewFamily& ViewFamily,
	uint32 VisibilityMap,
	FMeshElementCollector& Collector) const
{
	for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
	{
		if (VisibilityMap & (1 << ViewIndex))
		{
			FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);

			const float ParticleSize = Component->ParticleSize;
			
			const FVector OffsetLocation = Component->GetComponentLocation();
			DrawWireBox(PDI, FBox(OffsetLocation - FVector(100), OffsetLocation + FVector(100)),
						FLinearColor::Green, SDPG_World, 2);
			
			const TArray<FPSParticle>& Particles = Component->GetParticles();
			for (const FPSParticle& P : Particles)
			{
				PDI->DrawPoint(P.Position, P.Color, ParticleSize, SDPG_World);
			}
		}
	}
}