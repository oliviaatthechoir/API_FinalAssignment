#pragma warning (push)
#pragma warning (disable : 26481)
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
#pragma warning (pop)


Game::Game()
	: player({ GetScreenWidth() / 2.0f, GetScreenHeight() - 130.0f }),
	shipTextures{
		TextureResource("./Assets/Ship1.png"),
		TextureResource("./Assets/Ship2.png"),
		TextureResource("./Assets/Ship3.png")
	},
	alienTexture("./Assets/Alien.png"),
	barrierTexture("./Assets/Barrier.png"),
	laserTexture("./Assets/Laser.png")
{
}

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
	const auto pos = player.player_base_height; 
	const auto reachedEnding = [pos](const Alien& a) noexcept {
		return (a.position.y > static_cast<float>(GetScreenHeight()) - pos); 
	}; 
	return(IsKeyReleased(KEY_Q) || (player.lives < 1) || std::ranges::any_of(Aliens, reachedEnding)); 
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
		CheckAnyCollisions(); 
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
		//Code

		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);

		break;
	case State::GAMEPLAY:
		
		bg.Render();

		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

		//player rendering
		player.Render(shipTextures.at(player.activeTexture)); 


		//projectile rendering
		for (auto const& projectile : Projectiles)
		{
			projectile.Render(laserTexture);

		}

		// wall rendering 
		for (auto const& wall : Walls)
		{
			wall.Render(barrierTexture); 
		}

		//alien rendering  
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
			std::cout << "Find Alien -X:" << position.x << std::endl;
			std::cout << "Find Alien -Y:" << position.y << std::endl;
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

void Game::CheckAnyCollisions() {
	for (auto& projectile : Projectiles)
	{
		if (projectile.velocity.y < 0) {
			for (auto& alien : Aliens)
			{
				if (AABB(projectile, alien)) {
					alien.active = false;
					projectile.active = false;
					break;
				}
			}
		}

		if (projectile.velocity.y > 0 && AABB(projectile, player)) {
			projectile.active = false;
			player.lives--;
		}

		for (auto& wall : Walls) {
			if (AABB(projectile, wall)) {
				std::cout << "Hit wall at position: " << wall.position.x << ", health: " << wall.health << "\n";
				wall.health--;
				projectile.active = false;
				break;
			}
		}
	}

}

void Game::HandleAlienProjectile() noexcept {
	if (++shootTimer >= shootInterval && !Aliens.empty()) {
		shootTimer = 0;
		const size_t idx = static_cast<size_t>(GetRandomValue(0, static_cast<int>(Aliens.size()) - 1));
		const Alien& shooter = Aliens.at(idx);
		Vector2 spawnPos = shooter.GetGunPosition(); 
		Vector2 vel = { 0, 6 };
		Projectiles.emplace_back(spawnPos, vel);

	}

}

void Game::CleanEntities() {
	const auto isDead = [](const auto& a) noexcept {return !a.active;  };
	std::erase_if(Aliens, isDead);
	std::erase_if(Walls, isDead);
	std::erase_if(Projectiles, isDead);
}









































