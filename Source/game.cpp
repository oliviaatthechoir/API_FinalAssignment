#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include "Utilities.h"


//TODO: seperate functionalities here

const Background bg(100);


//// MATH FUNCTIONS
//float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
//{
//	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
//
//	return length;
//}
//
//bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
//{
//	float distanceToCentre = lineLength(circlePos, point);
//
//	if (distanceToCentre < radius)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}


void Game::Start()
{
	// creating walls 
	auto window_width = (float)GetScreenWidth(); 
	auto window_height = (float)GetScreenHeight(); 
	float wall_distance = window_width / (wallCount + 1); 
	for (int i = 0; i < wallCount; i++)
	{
		Wall newWalls;
		newWalls.position.y = window_height - 250; 
		newWalls.position.x = wall_distance * (i + 1); 

		Walls.push_back(newWalls); 

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

void Game::Launch()
{
	//LOAD SOME RESOURCES HERE
	resources.Load();
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

		////create projectile! 
		//if (IsKeyPressed(KEY_SPACE)) {
		//	Vector2 spawnPos = { player.position.x + player.size.x / 2, player.position.y };
		//	Projectiles.push_back(Projectile(spawnPos, { 0, -15.0f }));
		//}

		//shootTimer++; 
		//if (shootTimer > 59 && !Aliens.empty()) {
		//	int idx = GetRandomValue(0, static_cast<int>(Aliens.size()) - 1);
		//	Vector2 spawnPos = Aliens[idx].position; 
		//	spawnPos.y += Aliens[idx].size.y; 
		//	Projectiles.push_back(Projectile(spawnPos, { 0, 15.0f }));
		//	shootTimer = 0;
		//}


		for (auto it = Aliens.begin(); it != Aliens.end(); )
		{
			if (!it->active)
			{
				it = Aliens.erase(it); 
			}
			else
			{
				++it; 
			}
		}
		for (auto it = Walls.begin(); it != Walls.end(); )
		{
			if (!it->active)
			{
				it = Walls.erase(it); 
			}
			else
			{
				++it; 
			}
		}


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
		player.Render(resources.shipTextures[player.activeTexture]);

		//projectile rendering
		for (auto const& projectile : Projectiles)
		{
			projectile.Render(resources.laserTexture);
		}

		// wall rendering 
		for (auto const& wall : Walls)
		{
			wall.Render(resources.barrierTexture); 
		}

		//alien rendering  
		for (auto const& alien : Aliens)
		{
			alien.Render(resources.alienTexture);
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
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			auto newAlien = Alien();
			newAlien.active = true;
			newAlien.position.x = formationX + 450 + (col * alienSpacing);
			newAlien.position.y = formationY + (row * alienSpacing);
			Aliens.push_back(newAlien);
			std::cout << "Find Alien -X:" << newAlien.position.x << std::endl;
			std::cout << "Find Alien -Y:" << newAlien.position.y << std::endl;
		}
	}

}




void Wall::Render(Texture2D texture) const 
{
	DrawTexturePro(texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), position.x-21, position.y+10, 40, RED);
	
}

void Wall::Update() 
{

	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}


}

void Alien::Update() 
{
	int window_width = GetScreenWidth(); 

	if (moveRight)
	{
		position.x += speed; 

		if (position.x >= GetScreenWidth())
		{
			moveRight = false; 
			position.y += 50; 
		}
	}
	else 
	{
		position.x -= speed; 

		if (position.x <= 0)
		{
			moveRight = true; 
			position.y += 50; 
		}
	}
}

void Alien::Render(Texture2D texture) const 
{
	//TODO: scale the asset on the HD instead, and use the simpler DrawTexture call. just three arguments; texture, position, color. no scaling needed. 
	DrawTexturePro(texture,
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, {50 , 50},
		0,
		WHITE);
}




























