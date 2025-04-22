#include "raylib.h"
#include "Projectile.h"

Projectile::Projectile(Vector2 spawnPos, Vector2 vel) : Entity(spawnPos, vel, {10, 30}) {}

void Projectile::Update() {
	Entity::Update(); 

	if (position.y < -50 || position.y > 1500) active = false; 
}

void Projectile::Render(Texture2D texture) const {
	DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE); 
}