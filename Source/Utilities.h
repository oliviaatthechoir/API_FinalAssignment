#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Entity.h"
#include <string_view>

inline bool AABB(const Entity& a, const Entity& b) noexcept {
	return CheckCollisionRecs(a.GetRect(), b.GetRect()); 
}

inline void DrawTextCpp(std::string_view text, int x, int y, int fontSize, Color color) noexcept {
	DrawText(text.data(), x, y, fontSize, color);
}



