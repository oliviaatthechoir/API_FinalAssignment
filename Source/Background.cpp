#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
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

void Background::Update(float offset) noexcept
{
    for (auto& star : stars)
        star.Update(offset);
}

void Background::Render() const noexcept
{
    for (const auto& star : stars)
        star.Render();
}
