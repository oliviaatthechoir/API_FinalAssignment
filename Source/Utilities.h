#pragma once
#include "raylib.h"
#include "Entity.h"
#include <string_view>

bool AABB(const Entity& a, const Entity& b) {
	return CheckCollisionRecs(a.GetRect(), b.GetRect()); 
}

inline void DrawTextCpp(std::string_view text, int x, int y, int fontSize, Color color) {
	DrawText(text.data(), x, y, fontSize, color);
}

