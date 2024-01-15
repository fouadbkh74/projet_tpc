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





        if (editMode && key > 0) {
            // Accepter uniquement des chiffres pour l'entrée décimale
            if (isdigit(key) && strlen(inputText) < 2) {
                strcat(inputText, (char[]){(char)key, '\0'}); // Ajouter le caractère à la fin de la chaîne
            }
        }

        if (IsKeyPressed(KEY_ENTER) && strlen(inputText) > 0) {
            // Convertir la chaîne de caractères en une valeur entière décimale
            int inputValue = atoi(inputText);

            // Vérifier si la taille du nombre ne dépasse pas 2 chiffres
            if (inputValue >= 0 && inputValue <= 99) {
                // Faites quelque chose avec la valeur entière (inputValue)
                // Par exemple, imprimez-la :
                printf("Valeur saisie : %d\n", inputValue);
            } else {
                // La valeur n'est pas dans la plage spécifiée, gérer l'erreur
                printf("Erreur : La valeur doit être entre 0 et 99 inclus.\n");
            }

            // Réinitialiser la boîte de saisie
            inputText[0] = '\0';
        }

        if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputText) > 0) {
            inputText[strlen(inputText) - 1] = '\0'; // Retirer le dernier caractère
        } else {
            SetMouseCursor(editMode ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
        }














        BeginDrawing();
             DrawText("TRIE PAR COMPTAGE", windowWidth/2-200, 10, 40, BLUE);

        // Draw the border rectangle
        DrawRectangleLinesEx((Rectangle){ 10, 10, 160, 770 }, 4, BLUE);


        // Draw the green background rectangle
        DrawRectangleLinesEx((Rectangle){300, 150, 500, 500}, 4, BLUE);

        // Draw the buttons
        GuiButton(buttonBounds1, "trie");
        GuiButton(buttonBounds2, "entre");
        GuiButton(buttonBounds3, "exit");

        { ////// textbox n=
            // Dessiner la phrase "N=" avant le textBox
        DrawText("N=", windowWidth / 2 - 240, 710, 30, BLACK);

        DrawRectangleRec(textBox, (mouseOnText && editMode) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE); // BORDER

        // Dessiner le texte uniquement s'il y a du texte dans la boîte
        if (strlen(inputText) > 0) {
            // Mesurer la largeur du texte affiché
            int textWidth = MeasureText(inputText, 30);

            // Centrer le texte dans la boîte de texte
            DrawText(inputText, (int)textBox.x + (int)(textBox.width - textWidth) / 2, (int)textBox.y + (int)(textBox.height - 30) / 2, 30, BLACK);
        }}

        EndDrawing();
    }

    CloseWindow();

    return 0;
}