#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning(disable : 5592)
#include "raylib.h"
#pragma warning(pop)
#include <vector>
#include <string_view>
#include <stdexcept>
#include <utility>
#include <format>

// made a custom throw 

class TextureLoadException : public std::runtime_error {
public:
	using std::runtime_error::runtime_error;	
};


class TextureResource {
	Texture2D texture;
public:

	explicit TextureResource(const std::string_view& path) {
		texture = LoadTexture(path.data()); 
		if (texture.id <= 0) {
			throw TextureLoadException(std::format("Unable to load texture: {}", path));
		}
	}

	TextureResource() = delete;

	TextureResource(const TextureResource& other) = delete;
	TextureResource& operator=(const TextureResource& other) = delete;

	TextureResource(TextureResource&& other) noexcept
	{
		std::swap(other.texture, texture);
	}

	TextureResource& operator=(TextureResource&& other) noexcept {
		std::swap(other.texture, texture);
		return *this;
	}


	~TextureResource() {
		UnloadTexture(texture);
	}

	Texture2D Get() const noexcept { return texture; }



};
		




