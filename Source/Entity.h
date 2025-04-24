#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "TextureResource.h"

class Entity {
public: 
	Vector2 position = { 0,0 }; 
	Vector2 velocity = { 0, 0 }; 
	Vector2 size = { 0,0 }; 
	bool active = true; 

	Entity(Vector2 pos, Vector2 vel, Vector2 size) noexcept; 

	void Update(); 
	void Render(const TextureResource& texture) const noexcept; 
	Rectangle GetRect() const noexcept; 
};