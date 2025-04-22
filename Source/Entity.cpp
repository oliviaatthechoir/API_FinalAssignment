#include "Entity.h"

Entity::Entity(Vector2 pos, Vector2 vel, Vector2 size) : position(pos), velocity(vel), size(size), active(true) {}

void Entity::Update() {
	position.x += velocity.x; 
	position.y += velocity.y; 
}

void Entity::Render() const {
	DrawRectangleV(position, size, GRAY); 
}

Rectangle Entity::GetRect() const {
	return{ position.x, position.y, size.x, size.y }; 
}
