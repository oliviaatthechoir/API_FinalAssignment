#pragma once
#include "raylib.h"
#include "Entity.h"
#include "TextureResource.h"

class Alien : public Entity {
public: 
	bool moveRight = true;
	int speed = 2; 

	explicit Alien(Vector2 pos); 

	void Update(); 
	void Render(const TextureResource& texture) const; 
};