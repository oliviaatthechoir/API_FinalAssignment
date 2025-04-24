#include <CodeAnalysis/Warnings.h>
#pragma once
#include "raylib.h"
#include <stdexcept>

class Window {
	int screenWidth = 1920; 
	int screenHeight = 1080; 
public: 
	explicit Window(const std::string_view& title) {
		InitWindow(screenWidth, screenHeight, title.data()); 
		if (!IsWindowReady()) {
			throw std::runtime_error("failed to open window"); 
		}
		SetTargetFPS(60);
	}
	Window(const Window& other) = delete; 
	Window& operator=(const Window& other) = delete; 
	Window(Window&& other) = delete; 
	Window& operator=(Window&& other) = delete; 

	~Window() {
		CloseWindow(); 
	}
};
