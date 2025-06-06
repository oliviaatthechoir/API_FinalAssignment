﻿#pragma warning (push)
#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "Alien.h"
#include <cassert>
#include "raylib.h"
#include "TextureResource.h"
#include <span>

#pragma warning (disable : 26481)
#pragma warning(disable : 4201)
#pragma warning(disable : 4996)
#pragma warning(disable : 26472)
#pragma warning(disable : 26447)
#pragma warning(disable : 26446)
#pragma warning (pop)


void Game::Start()
{
	SpawnAliens();
	SpawnWalls(); 

	gameState = State::GAMEPLAY;

}

void Game::End() noexcept
{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	player.lives = 3;
	gameState = State::ENDSCREEN;
}

bool Game::CheckForGameOver() const noexcept {
	const auto collidedWithWall = [this](const Alien& alien) noexcept {
		return std::ranges::any_of(Walls, [&alien](const Wall& wall) noexcept {
			return AABB(alien, wall);
			});
		};


	return {
		IsKeyReleased(KEY_Q) ||
		(player.lives < 1) ||
		std::ranges::any_of(Aliens, collidedWithWall)
	};

}

void Game::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		if (IsKeyPressed(KEY_SPACE)) {
			Start(); 
		}
		break;
	case State::GAMEPLAY:
		if (CheckForGameOver()) {
			return End(); 
		}
		player.Update(); 

		for (auto& projectile : Projectiles)
		{
			projectile.Update(); 
		}

		for (auto& wall : Walls) {
			wall.Update(); 
		}

		for (auto& alien : Aliens) {
			alien.Update(); 
		}
		
		if (Aliens.empty()) {
			SpawnAliens();
		}

		if (IsKeyPressed(KEY_SPACE)) {
			Vector2 spawn = player.GetGunPosition(); 
			Vector2 velocity = { 0, -8 };
			Projectiles.emplace_back(spawn, velocity);

		}
		HandleAlienProjectile(); 
		CollisionHitCheck(); 
		CleanEntities(); 
		break;
	case State::ENDSCREEN:
		if (IsKeyPressed(KEY_ENTER)) {
			Start(); 
		}
		break;
	default:
		assert(false && "invalid game state"); 
		break;
	}
	
}


void Game::Render() noexcept
{
	BeginDrawing();
	ClearBackground(BLACK);
	switch (gameState)
	{
	case State::STARTSCREEN:

		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);

		break;
	case State::GAMEPLAY:
		
		bg.Render();

		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

		player.Render(); 

		for (auto const& projectile : Projectiles)
		{
			projectile.Render(laserTexture);

		}

		for (auto const& wall : Walls)
		{
			wall.Render(barrierTexture); 
		}

		for (auto const& alien : Aliens)
		{
			alien.Render(alienTexture);
		}

		break;
	case State::ENDSCREEN:
		DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

		break;
	default:
		
		break;
	}
	EndDrawing(); 
}


void Game::SpawnAliens()
{
	Aliens.clear(); 

	for (int row = 0; row < formationHeight; ++row) {
		for (int col = 0; col < formationWidth; ++col) {
			Vector2 position = {
				alienOrigin.x + (col * alienSpacing),
				alienOrigin.y + (row * alienSpacing)
			}; 
			Aliens.emplace_back(position);
		}
	}

}

void Game::SpawnWalls() {
	constexpr int wallCount = 5;
	const auto screenWidth = static_cast<float>(GetScreenWidth());
	const float wallY = static_cast<float>(GetScreenHeight()) - 340.0f;

	constexpr float wallWidth = 100.0f;
	const float totalSpacing = screenWidth - static_cast<float>(wallCount) * wallWidth;
	const float gap = totalSpacing / static_cast<float>(wallCount + 1) - 30.0f; 


	Walls.clear();
	Walls.reserve(wallCount);
	for (int i = 0; i < wallCount; ++i) {
		const float x = gap + (gap + wallWidth) * static_cast<float>(i);
		const Vector2 pos = { x, wallY };
		Walls.emplace_back(pos);
	}
}

void Game::CollisionHitCheck() noexcept {
	for (auto& projectile : Projectiles) {
		WallHitCheck(projectile);
		PlayerHitCheck(projectile);
		AlienHitCheck(projectile);
	}
	 

}

void Game::WallHitCheck(Projectile& projectile) noexcept {	
	for (auto& wall : Walls) {
		if (AABB(projectile, wall)) {
			wall.health--;
			projectile.active = false;
			return;
		}
	}
	
}

void Game::PlayerHitCheck(Projectile& projectile) noexcept {
	if (projectile.velocity.y > 0 && AABB(projectile, player)) {
		projectile.active = false;
		player.lives--;
	}
}

void Game::AlienHitCheck(Projectile& projectile) noexcept {
	if (projectile.velocity.y < 0) {
		for (auto& alien : Aliens) {
			if (AABB(projectile, alien)) {
				alien.active = false;
				projectile.active = false;
				return;
			}
		}
	}
}

void Game::HandleAlienProjectile() noexcept {
	const size_t size = Aliens.size();
	if (++shootTimer < shootInterval || size == 0) return;

	shootTimer = 0;

	size_t randomAlienIndex = 0;
	if (size > 1)
	{
		[[gsl::suppress(26472, justification: "I don't care about narrowing conversions here")]]
		const auto max = static_cast<int>(size - 1);		
		randomAlienIndex = static_cast<size_t>(GetRandomValue(0, max));
	}
	
	
	assert(randomAlienIndex >= 0 && randomAlienIndex < Aliens.size());
	[[gsl::suppress(26446, justification: "Span access is bounds-checked and safe here")]]
	const Alien& shooter = Aliens[randomAlienIndex];
	const Vector2 spawnPos = shooter.GetGunPosition();
	const Vector2 velocity = { 0, 6 };
	try {
		Projectiles.emplace_back(spawnPos, velocity);
	}
	catch (...) {
		assert(false && "hey, we ran out of memory apparently");
		//swallow. The game doesn't need to end because of a missing bullet
	}
}

void Game::CleanEntities() {
	const auto isDead = [](const auto& a) noexcept {return !a.active;  };
	std::erase_if(Aliens, isDead);
	std::erase_if(Walls, isDead);
	std::erase_if(Projectiles, isDead);
}









































