#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Entity.h"
#include "TextureResource.h"

class Projectile : public Entity {
public: 
	Projectile(Vector2 pos, Vector2 velocity) noexcept; 

	void Update() noexcept override; 
	void Render(const TextureResource& texture) const noexcept override; 
};

