#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Player.h"
#include "TextureResource.h"

Player::Player(Vector2 pos) noexcept : Entity(pos, { 0, 0 }, { 100, 100 }) {}


void Player::Update() {
	direction = 0; 

	if(IsKeyDown(KEY_LEFT)) direction--; 
	if (IsKeyDown(KEY_RIGHT)) direction++; 

	velocity.x = 7.0f * static_cast<float>(direction); 
	velocity.y = 0; 

	Entity::Update(); 

	timer += GetFrameTime(); 
	if (timer > 0.4f) {
		activeTexture = (activeTexture + 1) % 3; 
		timer = 0; 
	}
}

void Player::Render(const TextureResource& texture) const noexcept {
	DrawTexture(texture.Get(), static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
	
}

