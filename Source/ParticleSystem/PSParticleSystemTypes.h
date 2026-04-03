#pragma once

#include "PSTemplateParticleSystem.h"
#include "PSParticleTypes.h"
#include "PSParticlePolicies.h"

using FMovingParticleSystem = TParticleSystem<FMovingParticle, FMovingParticleUpdatePolicy, FMovingParticleSpawnPolicy>;
using FStaticParticleSystem = TParticleSystem<FStaticParticle, FStaticParticleUpdatePolicy, FStaticParticleSpawnPolicy>;