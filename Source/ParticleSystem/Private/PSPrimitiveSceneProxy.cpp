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

void FPSPrimitiveSceneProxy::GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const
{
	for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
	{
		if (VisibilityMap & (1 << ViewIndex))
		{
			FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
			
			const FVector& OffsetLocation = Component->GetComponentLocation();
			const FVector& GridSize = Component->GridSize;
			const float GridSpacing = Component->GridSpacing;
			const float ParticleSize = Component->ParticleSize;
			
			DrawWireBox(PDI, FBox(FVector(-ParticleSize) + OffsetLocation, GridSize * GridSpacing + ParticleSize + OffsetLocation), FLinearColor::Green, SDPG_World, 5);
			
			for (int32 x = 0; x < GridSize.X; x++)
			{
				for (int32 y = 0; y < GridSize.Y; y++)
				{
					for (int32 z = 0; z < GridSize.Z; z++)
					{
						PDI->DrawPoint(GridSpacing * FVector(x, y, z) + OffsetLocation, FLinearColor::Red, ParticleSize, SDPG_World);
					}
				}
			}
		}
	}
}