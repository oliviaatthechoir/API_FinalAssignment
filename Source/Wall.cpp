#include "raylib.h"
#include "Wall.h"
#include "Utilities.h"
#include <utility>
#include <string>
#include <format>

Wall::Wall(Vector2 pos) : Entity(pos, {0, 0}, {200, 200}) {}

void Wall::Update() {
	if (health <= 0) {
		active = false; 
	}
}

void Wall::Render(const TextureResource& texture) const {
    DrawTexture(texture.Get(), static_cast<int>(position.x), static_cast<int>(position.y), WHITE);

    int fontSize = 24;
    std::string text = std::format("{}", std::max(0, health));
    int textWidth = MeasureText(text.c_str(), fontSize); // still needed for width

    auto textX = static_cast<int>(position.x + size.x / 2 - static_cast<float>(textWidth) / 2);
    auto textY = static_cast<int>(position.y + size.y / 2 - static_cast<float>(fontSize) / 2 + 4);

    DrawTextCpp(text, textX, textY, fontSize, RED);
}
