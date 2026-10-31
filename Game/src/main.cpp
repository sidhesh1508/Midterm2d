#include "raylib.h"
#include "Hypotrochoid.h"

int main()
{
    int width = 800;
    int height =500;

    InitWindow(width, height, "Hypotrochoid Designs");

    SetTargetFPS(60);

    Hypotrochoid shape(200, 50, 50);

    int currentDesign = 0;

    const char* designNames[4] =
    {
        "Design 1 - Four Point Hypocycloid",
        "Design 2 - Four Looped Petals",
        "Design 3 - Five Point Hypocycloid",
        "Design 4 - Five Looped Petals"
    };

    while (!WindowShouldClose())
    {
        // Switch design when left mouse button is clicked
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentDesign++;

            if (currentDesign >= 4)
            {
                currentDesign = 0;
            }

            shape.SetDesign(currentDesign);
        }

        shape.Update();

        BeginDrawing();

        ClearBackground(BLACK);

        shape.Draw();

        DrawText(
            designNames[currentDesign],
            20, 20, 22, WHITE
        );

        DrawText(
            "Click anywhere to change design",
            20, 55, 18, GRAY
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}