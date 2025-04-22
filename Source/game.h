#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include "TextureResource.h"
#include "Background.h"
#include "Player.h"
#include "Projectile.h"
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

struct Alien
{
public:
	
	Color color = WHITE; 
	Vector2 position = {0, 0};
	int x = 0; 
	int y = 0; 
	float radius = 30;
	bool active = true;  
	bool moveRight = true; 


	int speed = 2; 
		 
	void Update(); 
	void Render(Texture2D texture) const; 
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

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;

	bool newHighScore = false;
	

	void Start();
	void End();

	void Continue();
	void Launch();

	void Update();
	void Render();

	void SpawnAliens();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom) const;


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