#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Projectile.h"

Projectile::Projectile(Vector2 pos, Vector2 vel) : Entity(pos, vel, {3, 15}) {}

void Projectile::Update() noexcept {
	Entity::Update(); 

	if (position.y < -size.y || position.y > static_cast<float>(GetScreenHeight())) {
		active = false; 
	}
}

void Projectile::Render(const TextureResource& texture) const noexcept{
	DrawTexture(texture.Get(), static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}