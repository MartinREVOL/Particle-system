#pragma once

#include "CoreMinimal.h"
#include "PSComponent.h"
#include "GameFramework/Actor.h"
#include "PSActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PARTICLESYSTEM_API APSActor : public AActor
{
	GENERATED_BODY()

public:
	APSActor();
	
	UPROPERTY(Category = PSActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPSComponent> PSComponent;
};
