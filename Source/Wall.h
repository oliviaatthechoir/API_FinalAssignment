#pragma once
#include "raylib.h"
#include "Entity.h"
#include "TextureResource.h"

class Wall : public Entity {
public: 
	int health = 50; 
	int radius = 60; 

	explicit Wall(Vector2 pos); 
	void Update(); 
	void Render(const TextureResource& texture) const; 
};