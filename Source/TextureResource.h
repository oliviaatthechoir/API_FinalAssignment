#pragma once
#include "raylib.h"
#include <string_view>
#include <stdexcept>

// made a custom throw 

class TextureLoadException : public std::runtime_error {
public:
	explicit TextureLoadException(const std::string_view& message) : std::runtime_error(std::string(message)) {}
};


class TextureResource {
public:
	explicit TextureResource(const std::string_view& path) : texture(LoadTexture(path.data())){
		if (texture.id <= 0) {
			//throw std::runtime_error("Unable to load texture");
			throw TextureLoadException("Unable to load texture" + std::string(path)); 
		}
	}

	~TextureResource() noexcept {
		UnloadTexture(texture);
	}

	TextureResource(const TextureResource&) = delete; 
	TextureResource& operator=(const TextureResource&) = delete; 

	TextureResource(TextureResource&& other) noexcept
		: texture(other.texture) {
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





