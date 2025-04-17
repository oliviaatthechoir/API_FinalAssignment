#pragma once
#include "raylib.h"
#include <string>

class TextureResource {
public: 
	TextureResource() : texture{}, loaded(false) {}

	explicit TextureResource(const std::string& path) : texture(LoadTexture(path.c_str())), loaded(true) {}

	~TextureResource() {
		if (loaded) {
			UnloadTexture(texture); 
		}
	}



	Texture2D Get() { return texture; }
	const Texture2D& Get() const { return texture; }
private: 
	Texture2D texture; 
	bool loaded = false; 

};
