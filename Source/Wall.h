#pragma once
#include "raylib.h"
#include "Entity.h"

class Wall : public Entity {
public: 
	int health = 50; 
	int radius = 60; 

	Wall(Vector2 pos); 
	void Update(); 
	void Render(Texture2D texture) const; 
};