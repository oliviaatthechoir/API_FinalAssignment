#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Entity.h"
#include "TextureResource.h"
#include <array>


class Player : public Entity {
public:
	std::array<TextureResource, 3> shipTextures{
	TextureResource("./Assets/Ship1.png"),
	TextureResource("./Assets/Ship2.png"),
	TextureResource("./Assets/Ship3.png")
	};

	int lives = 3;
	int direction = 0;
	size_t activeTexture = 0;
	float timer = 0;
	float player_base_height = 0;

	explicit Player(Vector2 pos) noexcept;


	void Update() noexcept override;
	void Render() const noexcept;

	Vector2 GetGunPosition() const noexcept;


};
