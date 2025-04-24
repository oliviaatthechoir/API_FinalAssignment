#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Entity.h"
#include "TextureResource.h"

class Player : public Entity {
public: 
	int lives = 3; 
	int direction = 0; 
	int activeTexture = 0; 
	float timer = 0;
	float player_base_height = 0; 

	explicit Player(Vector2 pos) noexcept; 

	
	void Update() override;
	void Render(const TextureResource& texture) const noexcept override; 

	
};
