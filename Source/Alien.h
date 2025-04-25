#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Entity.h"
#include "TextureResource.h"

class Alien : public Entity {
public: 
	bool moveRight = true;
	int speed = 2; 

	explicit Alien(Vector2 pos) noexcept; 

	void Update() noexcept override; 
	void Render(const TextureResource& texture) const noexcept override; 

	Vector2 GetGunPosition() const noexcept; 
};