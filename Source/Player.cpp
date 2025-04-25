#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Player.h"
#include "TextureResource.h"
#include <cassert>
Player::Player(Vector2 pos) noexcept : Entity(pos, { 0, 0 }, { 100, 100 }) {}


void Player::Update() noexcept {
	direction = 0; 

	if(IsKeyDown(KEY_LEFT)) direction--; 
	if (IsKeyDown(KEY_RIGHT)) direction++; 

	velocity.x = 7.0f * static_cast<float>(direction); 
	velocity.y = 0; 

	Entity::Update(); 

	timer += GetFrameTime(); 
	if (timer > 0.4f) {
		activeTexture = (activeTexture + 1) % shipTextures.size();
		timer = 0; 
	}
}

void Player::Render() const noexcept {
	assert(activeTexture < shipTextures.size());
	[[gsl::suppress(26446, justification: "The index is guarantueed to be valid.")]]
	const auto& tex = shipTextures[activeTexture];
	DrawTexture(tex.Get(), static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
	
}

Vector2 Player::GetGunPosition() const noexcept {
	return { position.x + size.x / 2.0f - 5.0f,
	position.y }; 
}

