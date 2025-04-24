#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
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

void Alien::Render(const TextureResource& texture) const noexcept {
	DrawTexture(texture.Get(), static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}

Vector2 Alien::GetGunPosition() const noexcept {
    return {
        position.x + size.x / 2 - 5,  // Horizontal center
        position.y + size.y          // Bottom of alien
    };
}
