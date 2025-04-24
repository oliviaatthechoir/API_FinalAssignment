#include <CodeAnalysis/Warnings.h>
#pragma once
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <vector>


class Star {
public:
    Star(Vector2 initPos, float starSize, Color starColor = BLUE) noexcept :
        initPosition(initPos), position(initPos), size(starSize), color(starColor)  {
    }

    void Update(float starOffset) noexcept {
        position.x = initPosition.x + starOffset;
        position.y = initPosition.y;
    }

    void Render() const noexcept {
        DrawCircleV(position, size, color);
    }

private:
    Vector2 initPosition = { 0, 0 };
    Vector2 position = { 0,0 };
    float size = 0;
    Color color = BLUE;
};


class Background {
public:
    explicit Background(int starAmount);
    void Update(float offset) noexcept;
    void Render() const noexcept;

private:
    std::vector<Star> stars;
};



