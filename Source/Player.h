#pragma once
#include "raylib.h"
#include "Entity.h"

class Player : public Entity {
public: 
	int lives = 3; 
	int direction = 0; 
	int activeTexture = 0; 
	float timer = 0;

	explicit Player(Vector2 pos); 
	void Update(); 
	void Render(Texture2D texture) const; 
};
