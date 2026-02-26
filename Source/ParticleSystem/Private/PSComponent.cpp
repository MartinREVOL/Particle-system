// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleSystem/Public/PSComponent.h"

#include "ParticleSystem/Public/PSPrimitiveSceneProxy.h"


UPSComponent::UPSComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	NbrParticules = 25;
}

void UPSComponent::BeginPlay()
{
	Super::BeginPlay();

	GridSize.X = NbrParticules;
	GridSize.Y = NbrParticules;
	GridSize.Z = NbrParticules;

	ParticleSystem.Init(MaxParticles, SpawnRate);
}

void UPSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UPSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MarkRenderStateDirty();
}

FPrimitiveSceneProxy* UPSComponent::CreateSceneProxy()
{
	return new FPSPrimitiveSceneProxy(this);
}

FBoxSphereBounds UPSComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	return FBoxSphereBounds(FBox(FVector::ZeroVector, GridSize * GridSpacing));
}

