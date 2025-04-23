#pragma once
#include "raylib.h"
#include "TextureResource.h"
#include "vector"
#include <string_view>


struct Resources {
	Resources(); 
	~Resources() = default; 

	std::vector<TextureResource> shipTextures;
	TextureResource alienTexture;
	TextureResource barrierTexture;
	TextureResource laserTexture;

};