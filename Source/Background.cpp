#include "raylib.h"
#include "Background.h"

Background::Background(int starAmount)
{
    stars.reserve(starAmount);
    for (int i = 0; i < starAmount; ++i)
    {
        Vector2 initPos = {
            static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)),
            static_cast<float>(GetRandomValue(0, GetScreenHeight()))
        };
        auto size = static_cast<float>(GetRandomValue(1, 4));
        stars.emplace_back(initPos, size);
    }
}

void Background::Update(float offset)
{
    for (auto& star : stars)
        star.Update(offset);
}

void Background::Render() const
{
    for (const auto& star : stars)
        star.Render();
}
