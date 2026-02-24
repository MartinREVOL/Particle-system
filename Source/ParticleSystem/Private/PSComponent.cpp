// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleSystem/Public/PSComponent.h"

#include "ParticleSystem/Public/PSPrimitiveSceneProxy.h"


UPSComponent::UPSComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UPSComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UPSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	SetRelativeLocation(FVector(100 * sin(GetWorld()->GetTimeSeconds()), 0, 0));
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

