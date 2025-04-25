#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Entity.h"
#include "TextureResource.h"

class Wall : public Entity {
public: 
	int health = 50; 
	int radius = 60; 

	explicit Wall(Vector2 pos) noexcept; 
	void Update() noexcept override; 
	void Render(const TextureResource& texture) const noexcept override;
	
};