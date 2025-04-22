#include "raylib.h"
#include "Alien.h"

Alien::Alien(Vector2 pos) : Entity(pos, { 0, 0 }, { 100, 100 }) {}

void Alien::Update() {
    if (moveRight) {
        velocity.x = static_cast<float>(speed);
        if (position.x + size.x >= static_cast<float>(GetScreenWidth())) {
            moveRight = false;
            position.y += size.y; // descend one row
        }
    }
    else {
        velocity.x = static_cast<float>(-speed);
        if (position.x <= 0) {
            moveRight = true;
            position.y += size.y;
        }
    }

	Entity::Update(); 
}

void Alien::Render(Texture2D texture) const {
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE); 
}
