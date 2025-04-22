#pragma once
#include "raylib.h"
#include <vector>


class Star {
public:
    Star(Vector2 initPos, float starSize, Color starColor = WHITE) :
        initPosition(initPos), position(initPos), size(starSize), color(starColor) {
    }

    void Update(float starOffset) {
        position.x = initPosition.x + starOffset;
        position.y = initPosition.y;
    }

    void Render() const {
        DrawCircleV(position, size, color);
    }

private:
    Vector2 initPosition = { 0, 0 };
    Vector2 position = { 0,0 };
    float size = 0;
    Color color = WHITE;
};


class Background {
public:
    explicit Background(int starAmount);
    void Update(float offset);
    void Render() const;

private:
    std::vector<Star> stars;
};



