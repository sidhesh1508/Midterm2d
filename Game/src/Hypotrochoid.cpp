#include "Hypotrochoid.h"
#include <cmath>

Hypotrochoid::Hypotrochoid(float R, float r, float d)
{
    center.x = GetScreenWidth() / 2.0f;
    center.y = GetScreenHeight() / 2.0f;

    SetDesign(0);
}

void Hypotrochoid::SetDesign(int design)
{
    // Reset animation
    angle = 0.0f;
    curvePoints.clear();

    // Select design
    switch (design)
    {
    case 0:
        R = 200.0f;
        r = 50.0f;
        d = 50.0f;
        break;

    case 1:
        R = 200.0f;
        r = 50.0f;
        d = 90.0f;
        break;

    case 2:
        R = 200.0f;
        r = 40.0f;
        d = 40.0f;
        break;

    case 3:
        R = 200.0f;
        r = 40.0f;
        d = 100.0f;
        break;
    }

    smallCircleCenter = CalculateSmallCircleCenter(angle);
    tracingPoint = CalculateTracingPoint(angle);

    UpdateDots();
}

Vector2 Hypotrochoid::CalculateSmallCircleCenter(float t)
{
    Vector2 point;

    point.x = center.x + (R - r) * cos(t);
    point.y = center.y + (R - r) * sin(t);

    return point;
}

Vector2 Hypotrochoid::CalculateTracingPoint(float t)
{
    Vector2 point;

    float ratio = (R - r) / r;

    point.x = center.x
        + (R - r) * cos(t)
        + d * cos(ratio * t);

    point.y = center.y
        + (R - r) * sin(t)
        - d * sin(ratio * t);

    return point;
}

void Hypotrochoid::UpdateDots()
{
    float rotation = -angle * ((R - r) / r);

    float dotDistance = r * 0.65f;

    for (int i = 0; i < 4; i++)
    {
        float currentAngle = rotation + i * (PI / 2.0f);

        dots[i].x = smallCircleCenter.x
            + dotDistance * cos(currentAngle);

        dots[i].y = smallCircleCenter.y
            + dotDistance * sin(currentAngle);
    }
}

void Hypotrochoid::Update()
{
    angle += 0.015f;

    smallCircleCenter = CalculateSmallCircleCenter(angle);
    tracingPoint = CalculateTracingPoint(angle);

    UpdateDots();

    curvePoints.push_back(tracingPoint);
}

void Hypotrochoid::Draw()
{
    // Large fixed circle
    DrawCircleLines(
        (int)center.x,
        (int)center.y,
        R,
        WHITE
    );

    // Draw curve
    for (int i = 1; i < (int)curvePoints.size(); i++)
    {
        DrawLineEx(
            curvePoints[i - 1],
            curvePoints[i],
            2.0f,
            SKYBLUE
        );
    }

    // Draw small rolling circle
    DrawCircleLines(
        (int)smallCircleCenter.x,
        (int)smallCircleCenter.y,
        r,
        GREEN
    );

    // Connect circle centres
    DrawLineEx(
        center,
        smallCircleCenter,
        1.0f,
        GRAY
    );

    // Draw four rotating dots
    for (int i = 0; i < 4; i++)
    {
        DrawCircleV(dots[i], 5.0f, ORANGE);
    }

    // Connect tracing point
    DrawLineEx(
        smallCircleCenter,
        tracingPoint,
        1.5f,
        YELLOW
    );

    // Draw tracing point
    DrawCircleV(tracingPoint, 5.0f, RED);
}