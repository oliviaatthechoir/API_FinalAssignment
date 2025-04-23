#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "Alien.h"


//TODO: seperate functionalities here

const Background bg(100);



void Game::Start()
{
	//creating walls 
	int wallCount = 5;
	auto screenWidth = static_cast<float>(GetScreenWidth());
	float wallY = static_cast<float>(GetScreenHeight()) - 340.0f; // place above player

	float wallWidth = 100.0f; // match the actual wall size you're using
	float totalSpacing = screenWidth - static_cast<float>(wallCount) * wallWidth;
	float gap = totalSpacing / static_cast<float>(wallCount + 1) - 30.0f; // ⬅️ manual left shift


	Walls.clear();
	for (int i = 0; i < wallCount; ++i) {
		float x = gap + (gap + wallWidth) * i;
		Vector2 pos = { x, wallY };
		Walls.emplace_back(pos);
	}


	//creating player
	player = Player(Vector2{ GetScreenWidth() / 2.0f, static_cast<float>(GetScreenHeight()) - 100 });

	
	//creating aliens
	SpawnAliens();
	

	gameState = State::GAMEPLAY;

}

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	gameState = State::STARTSCREEN;
}


void Game::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		//Code 
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();


		}

		break;
	case State::GAMEPLAY:
		//Code
		if (IsKeyReleased(KEY_Q))
		{
			End();
		}


		//Update Player
		player.Update();
		
		//Update Aliens and Check if they are past player
		for (auto& alien : Aliens)
		{
			alien.Update(); 

			if (alien.position.y >  GetScreenHeight()) 
			{
				End();
			}
		}

		//End game if player dies
		if (player.lives < 1)
		{
			End();
		}

		//Spawn new aliens if aliens run out
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}


		for (auto& projectile : Projectiles) {
			projectile.Update(); 
		}

		if (IsKeyPressed(KEY_SPACE)) {
			Vector2 spawn = { player.position.x + player.size.x / 2 - 5,
			player.position.y };

			Vector2 velocity = { 0, -8 };
			Projectiles.emplace_back(spawn, velocity);
		}

		if (++shootTimer >= shootInterval && !Aliens.empty()) {
			shootTimer = 0;
			int idx = GetRandomValue(0, static_cast<int>(Aliens.size()) - 1);
			const Alien& shooter = Aliens[idx];
			Vector2 spawnPos = {
				shooter.position.x + shooter.size.x / 2 - 5,
				shooter.position.y + shooter.size.y
			};

			Vector2 vel = { 0, 6 };
			Projectiles.emplace_back(spawnPos, vel);

		}

		//AABB!!!
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
					wall.health--;
					projectile.active = false;
					break;
				}
			}
		}

		std::erase_if(Aliens, [](const Alien& a) {return !a.active;  });
		std::erase_if(Walls, [](const Wall& w) {return !w.active;  });


		std::erase_if(Projectiles, [](const Projectile& p) { return !p.active; });

	break;
	case State::ENDSCREEN:
		//Code
	
		if (IsKeyPressed(KEY_ENTER)) {
			Start(); 
		}

		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}


void Game::Render()
{
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
		player.Render(resources.shipTextures[0].Get());


		//projectile rendering
		for (auto const& projectile : Projectiles)
		{
			projectile.Render(resources.laserTexture.Get());

		}

		// wall rendering 
		for (auto const& wall : Walls)
		{
			wall.Render(resources.barrierTexture.Get()); 
		}

		//alien rendering  
		for (auto const& alien : Aliens)
		{
			alien.Render(resources.alienTexture.Get());
		}


		break;
	case State::ENDSCREEN:
		DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

		break;
	default:
		
		break;
	}
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






































