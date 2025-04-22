#pragma once
#include "raylib.h"
#include "Entity.h"

class Projectile : public Entity {
public: 
	Projectile(Vector2 spawnPos, Vector2 velocity); 

	void Update(); 
	void Render(Texture2D texture) const; 
};
