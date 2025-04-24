#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <vector>
#include "TextureResource.h"
#include "Background.h"
#include "Player.h"
#include "Projectile.h"
#include "Alien.h"
#include "Wall.h"
#include <string>
#include <array>

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};


class Game
{
public: 
	Game() noexcept; 
	std::array<TextureResource, 3> shipTextures{
		TextureResource{"./Assets/Ship1.png"},
		TextureResource{"./Assets/Ship2.png"},
		TextureResource{"./Assets/Ship3.png"} }; 
	TextureResource alienTexture{ "./Assets/Alien.png" };
	TextureResource barrierTexture{ "./Assets/Barrier.png" };
	TextureResource laserTexture{ "./Assets/Laser.png" };


	// Gamestate
	State gameState = {};

	//Aliens shooting
	int shootTimer = 0;
	int shootInterval = 60; 


	//Alien formation data! 
	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	Vector2 alienOrigin = { 450, 50 }; 
	

	void Start();
	void End();
	void Continue(); 
	void Update(); 

	void Render();

	void SpawnAliens();
	void CleanEntities(); 

	Player player;

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	Background bg = Background(100);


	int framesCounter = 0;

	
	

};