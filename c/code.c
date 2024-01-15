#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <raygui.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(void) {
    const int windowWidth = 1000;
    const int windowHeight = 800;



    InitWindow(windowWidth, windowHeight, "2D Button Raylib");
int key = GetCharPressed();
    Rectangle buttonBounds1 = { 30, 50, 120, 50 };
    Rectangle buttonBounds2 = { 30, 130, 120, 50 };
    Rectangle buttonBounds3 = { 30, 700, 120, 50 };

        Rectangle textBox = {windowWidth / 2 - 200, 700, 100, 50};
 bool mouseOnText = false;
    bool editMode = false;
    char inputText[3] = "\0"; // Pour un entier décima

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
            mouseOnText = true;

            // Activer le mode d'édition si la souris est pressée
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                editMode = !editMode;
            }
        } else {
            mouseOnText = false;
        }





        BeginDrawing();
             DrawText("TRIE PAR COMPTAGE", windowWidth/2-200, 10, 40, BLUE);

        // Draw the border rectangle
        DrawRectangleLinesEx((Rectangle){ 10, 10, 160, 770 }, 4, BLUE);


        // Draw the buttons
        GuiButton(buttonBounds1, "trie");
        GuiButton(buttonBounds2, "entre");
        GuiButton(buttonBounds3, "exit");



        EndDrawing();
    }

    CloseWindow();

    return 0;
}
