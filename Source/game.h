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
#include <optional>
#include <string_view>

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};


class Game
{
public: 

	TextureResource alienTexture{ "./Assets/Alien.png" };
	TextureResource barrierTexture{ "./Assets/Barrier.png" };
	TextureResource laserTexture{ "./Assets/Laser.png" };

	State gameState = {};

	int shootTimer = 0;
	int shootInterval = 60; 
	bool gameOver = false; 

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	Vector2 alienOrigin = { 450, 50 }; 


	
	void End() noexcept;
	void SpawnAliens();
	void SpawnWalls(); 
	void CleanEntities(); 
	bool CheckForGameOver() const noexcept; 
	void CollisionHitCheck() noexcept; 
	void HandleAlienProjectile() noexcept; 
	void WallHitCheck(Projectile& projectile) noexcept; 
	void PlayerHitCheck(Projectile& projectile) noexcept; 
	void AlienHitCheck(Projectile& projectile) noexcept; 
	

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	Background bg = Background(100);

	Player player{ { GetScreenWidth() / 2.0f, GetScreenHeight() - 130.0f } };

	void Start();
	void Update();
	void Render() noexcept;

	bool isGameOver() const noexcept { return gameOver; }	

};