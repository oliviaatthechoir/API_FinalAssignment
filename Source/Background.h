#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>

class Star {
public: 
	Star(Vector2 initPos, float starSize, Color starColor = WHITE) :
		initPosition(initPos), position(initPos), size(starSize), color(starColor) { }

	void Update(float starOffset); 
	void Render() const; 

private: 
	Vector2 initPosition = { 0, 0 }; 
	Vector2 position = { 0,0 }; 
	float size = 0; 
	Color color = WHITE; 
};

class Background {
public: 
	Background(int starAmount) {
		Initialize(starAmount); 
	}

	void Update(float offset); 
	void Render() const; 

private: 
	std::vector<Star> stars; 
	void Initialize(int starAmount); 
	
};

void Background::Initialize(int starAmount)
{
	Star.reserve(starAmount);
	for (int i = 0; i < starAmount; i++)
	{
		//TODO: two-phase initialization. The constructor shoud always initialize the object fully. 
		Star newStar;

		newStar.initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
		newStar.initPosition.y = GetRandomValue(0, GetScreenHeight());

		newStar.size = GetRandomValue(1, 4) / static_cast<float>(2);

		Stars.push_back(newStar);

	}
}

void Background::Update(float offset)
{
	for (auto& star : Stars) {
		star.Update(offset);
	}
}

void Background::Render() const
{
	for (const auto& star : Stars) {
		star.Render();
	}
}