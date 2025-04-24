#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include "TextureResource.h"
#include "Background.h"
#include "Player.h"
#include "Projectile.h"
#include "Alien.h"
#include "Wall.h"
#include <string>

//TODO: seperate functionalities here 

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};


struct Game
{
	//TODO: an example of how to use RAII to make safe use of resources as a members. Either everything loads and initializes correctly or Game will never construct.
	TextureResource alien = TextureResource("./Assets/Alien.png"); 



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

	Player player; 

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	Background bg = Background(100);


	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;

	int framesCounter = 0;
private: 
	// Entity Storage and Resources
	Resources resources;

};