#pragma once
#include "raylib.h"
#include "Entity.h"

class Alien : public Entity {
public: 
	bool moveRight = true;
	int speed = 2; 

	Alien(Vector2 pos); 

	void Update(); 
	void Render(Texture2D texture) const; 
};