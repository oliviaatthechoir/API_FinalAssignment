#include "Resources.h"
#include <iostream>;

void Resources::Load()
{
	alienTexture = LoadTexture("./Assets/Alien.png");
	barrierTexture = LoadTexture("./Assets/Barrier.png");
	shipTextures.push_back(LoadTexture("./Assets/Ship1.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship2.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship3.png"));
	laserTexture = LoadTexture("./Assets/Laser.png");
}


void Resources::Unload() {
	UnloadTexture(alienTexture); 
	UnloadTexture(barrierTexture); 
	UnloadTexture(laserTexture); 

	for (Texture2D const& tex : shipTextures) {
		UnloadTexture(tex); 
	}
	shipTextures.clear(); 
}