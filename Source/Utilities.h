#pragma once
#include "raylib.h"
#include "Entity.h"

bool AABB(const Entity& a, const Entity& b) {
	return CheckCollisionRecs(a.GetRect(), b.GetRect()); 
}
