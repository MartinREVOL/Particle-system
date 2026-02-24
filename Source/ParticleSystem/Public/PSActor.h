#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PARTICLESYSTEM_API APSActor : public AActor
{
	GENERATED_BODY()

public:
	APSActor();
	
private:
	UPROPERTY(Category = PSActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPSComponent> PSComponent;
};
