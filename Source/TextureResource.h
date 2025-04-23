#pragma once
#include "raylib.h"
#include <string_view>
#include <stdexcept>

class TextureResource {
public:
	explicit TextureResource(const std::string_view& path) : texture(LoadTexture(path.data())){
		if (texture.id <= 0) {
			throw std::runtime_error("Unable to load texture");
		}
	}

	~TextureResource() noexcept {
		UnloadTexture(texture);
	}

	TextureResource(const TextureResource&) = delete; 
	TextureResource& operator=(const TextureResource&) = delete; 

	TextureResource(TextureResource&& other) noexcept {
		texture = other.texture; 
		other.texture = {}; 
	}

	TextureResource& operator=(TextureResource&& other) noexcept {
		if (this != &other) {
			UnloadTexture(texture); 
			texture = other.texture; 
			other.texture = {}; 
		}
		return *this; 
	}


	const Texture2D& Get() const noexcept { return texture; }
private:
	Texture2D texture;

};


