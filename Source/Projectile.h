#pragma once
#include "raylib.h"
#include "Entity.h"
#include "TextureResource.h"

class Projectile : public Entity {
public: 
	Projectile(Vector2 pos, Vector2 velocity); 

	void Update(); 
	void Render(const TextureResource& texture) const; 
};

