#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning (push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning(disable : 5592)
#include "raylib.h"
#include <stdexcept>
#include <string>

class WindowException : public std::runtime_error {
public: 
	explicit WindowException(const std::string& message) : std::runtime_error(message) {}
};

class Window {
	int screenWidth = 1920; 
	int screenHeight = 1080; 
public: 
	explicit Window(const std::string_view& title) {
		InitWindow(screenWidth, screenHeight, title.data()); 
		if (!IsWindowReady()) {
			throw WindowException("failed to open window"); 
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
