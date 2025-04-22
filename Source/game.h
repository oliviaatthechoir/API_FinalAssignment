#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include "TextureResource.h"
#include "Background.h"
#include "Player.h"
#include "Projectile.h"
#include "Alien.h"
#include <string>

//TODO: seperate functionalities here 

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};


struct Wall 
{
public: 
	Vector2 position; 
	Rectangle rec; 
	bool active; 
	Color color; 
	int health = 50;
	int radius = 60;


	void Render(Texture2D texture) const; 
	void Update(); 
};




struct Game
{

	//TODO: an example of how to use RAII to make safe use of resources as a members. Either everything loads and initializes correctly or Game will never construct.
	TextureResource alien = TextureResource("./Assets/Alien.png"); 


	// Gamestate
	State gameState = {};

	// for later, make a file where you can adjust the number of walls (config file) 
	int wallCount = 5;

	//Aliens shooting
	float shootTimer = 0;


	//Alien formation data! 
	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	Vector2 alienOrigin = { 450, 50 }; 
	

	void Start();
	void End();

	void Continue();
	void Launch();

	void Update();
	void Render();

	void SpawnAliens();


	// Entity Storage and Resources
	Resources resources;

	Player player; 

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	Background bg = Background(100);


	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;

	int framesCounter = 0;

};