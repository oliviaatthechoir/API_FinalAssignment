#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <string_view>
#include <stdexcept>
#include <utility>

// made a custom throw 

class TextureLoadException : public std::runtime_error {
public:
	explicit TextureLoadException(const std::string_view& message) : std::runtime_error(message.data()) {}
};


class TextureResource {
	Texture2D texture;
public:
	explicit TextureResource(const std::string_view& path) {
		texture = LoadTexture(path.data()); 
		if (texture.id <= 0) {
			throw TextureLoadException("Unable to load texture");
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

	const Texture2D& Get() const noexcept { return texture; }


};
		




