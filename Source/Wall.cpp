#include "raylib.h"
#include "Wall.h"
#include <utility>

Wall::Wall(Vector2 pos) : Entity(pos, {0, 0}, {200, 200}) {}

void Wall::Update() {
	if (health <= 0) {
		active = false; 
	}
}

void Wall::Render(Texture2D texture) const {
    // Draw the wall sprite
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);

    // Draw the health number inside the wall
    const char* text = TextFormat("%i", std::max(0, health));
    int fontSize = 28; // better size for inside display
    int textWidth = MeasureText(text, fontSize);

    auto textX = static_cast<int>(position.x + size.x / 2 - static_cast<float>(textWidth) / static_cast<float>(2));
    auto textY = static_cast<int>(position.y + size.y / 2 - 24 / 2 + 4);


    DrawText(text, textX, textY, fontSize, RED);
}
