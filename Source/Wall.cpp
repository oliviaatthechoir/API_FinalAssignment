#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Wall.h"
#include "Utilities.h"
#include <utility>
#include <string>
#include <format>

Wall::Wall(Vector2 pos) noexcept : Entity(pos, {0, 0}, {200, 200}) {}

void Wall::Update() noexcept {
	if (health <= 0) {
		active = false; 
	}
}

void Wall::Render(const TextureResource& texture) const noexcept{
    DrawTexture(texture.Get(), static_cast<int>(position.x), static_cast<int>(position.y), WHITE);

    constexpr int fontSize = 20;

    const std::string text = std::to_string(health);
    const int textWidth = MeasureText(text.data(), fontSize);
    constexpr int textHeight = fontSize;

    const float textX = position.x + (size.x - static_cast<float>(textWidth)) / 2.0f;
    const float textY = position.y + (size.y - static_cast<float>(textHeight)) / 2.0f;

    DrawText(text.data(), static_cast<int>(textX), static_cast<int>(textY), fontSize, RED);
   

}


