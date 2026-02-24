#pragma once

#include "CoreMinimal.h"
#include "PSComponent.h"

class PARTICLESYSTEM_API FPSPrimitiveSceneProxy : public FPrimitiveSceneProxy
{
public:
	FPSPrimitiveSceneProxy(const UPSComponent* InComponent);
	virtual ~FPSPrimitiveSceneProxy() override;
	
	SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<size_t>(&UniquePointer);
	}
	virtual uint32 GetMemoryFootprint( void ) const override { return( sizeof( *this ) + GetAllocatedSize() ); }
	SIZE_T GetAllocatedSize( void ) const { return FPrimitiveSceneProxy::GetAllocatedSize(); }

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;
	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;
	
private:
	const UPSComponent* Component;
};
