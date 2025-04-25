#include "Entity.h"
#include "TextureResource.h"

Entity::Entity(Vector2 pos, Vector2 vel, Vector2 size) noexcept : position(pos), velocity(vel), size(size), active(true) {}

void Entity::Update() noexcept {
	position.x += velocity.x; 
	position.y += velocity.y; 
}

void Entity::Render(const TextureResource& texture) const noexcept{
	DrawTextureV(texture.Get(), size, GRAY);
}

Rectangle Entity::GetRect() const noexcept {
	return{ position.x, position.y, size.x, size.y }; 
}
