#pragma once
#include "raylib.h"
#include <vector>

class Hypotrochoid
{
private:
    float R;
    float r;
    float d;
    float angle;

    Vector2 center;
    Vector2 smallCircleCenter;
    Vector2 tracingPoint;

    Vector2 dots[4];

    std::vector<Vector2> curvePoints;

    Vector2 CalculateSmallCircleCenter(float t);
    Vector2 CalculateTracingPoint(float t);
    void UpdateDots();

public:
    Hypotrochoid(float R, float r, float d);

    void SetDesign(int design);

    void Update();
    void Draw();
};