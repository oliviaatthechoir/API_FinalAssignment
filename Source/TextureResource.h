#pragma once
#include "raylib.h"
#include <string_view>
#include <stdexcept>

class TextureResource {
public:
	explicit TextureResource(std::string_view path) : texture(LoadTexture(path.data())){
		if (texture.id <= 0) {
			throw std::runtime_error("Unable to load texture");
		}
	}

	~TextureResource() noexcept {
		UnloadTexture(texture);
	}

	//TODO: = delete; copy constructors
	//TODO: define or delete move constructors 

	
	const Texture2D& Get() const noexcept { return texture; }
private:
	Texture2D texture;

};


