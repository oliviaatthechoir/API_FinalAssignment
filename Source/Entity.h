#pragma once
#include "raylib.h"

class Entity {
public: 
	Vector2 position = { 0,0 }; 
	Vector2 velocity = { 0, 0 }; 
	Vector2 size = { 0,0 }; 
	bool active = true; 

	Entity() = default; 

	Entity(Vector2 pos, Vector2 vel, Vector2 size); 

	void Update(); 
	void Render() const; 
	Rectangle GetRect() const; 
};