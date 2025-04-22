#include "raylib.h"
#include "Projectile.h"

Projectile::Projectile(Vector2 pos, Vector2 vel) : Entity(pos, vel, {10, 30}) {}

void Projectile::Update() {
	Entity::Update(); 

	if (position.y < -size.y || position.y > static_cast<float>(GetScreenHeight())) {
		active = false; 
	}
}

void Projectile::Render(Texture2D texture) const {
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE); 
}