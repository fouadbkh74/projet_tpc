#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

#define MAX_INPUT_CHARS1 2
#define NUMBERS_COUNT1 8

void DrawButtonWithText(Rectangle bounds, const char *text, int fontSize, bool isMouseOnButton) {
    DrawRectangleRec(bounds, isMouseOnButton ? DARKGRAY : LIGHTGRAY);
    DrawRectangleLinesEx((Rectangle){bounds.x, bounds.y, bounds.width, bounds.height}, 2, BLUE);

    // Calculer la position du texte pour le centrer dans le bouton
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 2);
    Vector2 textPosition = {bounds.x + bounds.width / 2 - textSize.x / 2, bounds.y + bounds.height / 2 - textSize.y / 2};

    DrawTextEx(GetFontDefault(), text, textPosition, fontSize, 2, BLUE);
}

int main(void) {
    const int windowWidth = 1000;
    const int windowHeight = 800;

    InitWindow(windowWidth, windowHeight, "projet tp c");

    Rectangle buttonBounds1 = {30, 50, 120, 50};
    Rectangle buttonBounds2 = {30, 130, 120, 50};
    Rectangle buttonBounds3 = {30, 700, 120, 50};

    Rectangle rectangles[10];
    Rectangle textBox = {windowWidth / 2 - 200, 700, 100, 50};
    bool mouseOnText = false;
    bool editMode = false;
    char inputText[3] = "\0"; // Pour un entier décimal
    int i;

    ///////////////////////////////////////
    Rectangle textBox1 = {windowWidth / 2 - 10, 700, 400, 50};
    bool mouseOnText1 = false;
    bool editMode1 = false;
    char inputText1[MAX_INPUT_CHARS1 + 1] = "\0"; // +1 for the null terminator

    int numbers1[NUMBERS_COUNT1];  // Tableau pour stocker les nombres saisis
    int numbersCount1 = 0;
    int cpt1 = 0; // Variable pour compter le nombre de saisies

    while (!WindowShouldClose()) {
        ClearBackground(WHITE);

        // Gestion de la première boîte de texte
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
            mouseOnText = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                editMode = !editMode;
                editMode1 = false; // Désactiver le mode d'édition de la deuxième boîte de texte
            }
        } else {
            mouseOnText = false;
        }

        // Gestion de la deuxième boîte de texte
        if (CheckCollisionPointRec(GetMousePosition(), textBox1)) {
            mouseOnText1 = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                editMode1 = !editMode1;
                editMode = false; // Désactiver le mode d'édition de la première boîte de texte
            }
        } else {
            mouseOnText1 = false;
        }

        // Gestion de la première boîte de texte
        if (editMode) {
            int key = GetKeyPressed();
            if (key > 0) {
                if (isdigit(key) && strlen(inputText) < 2) {
                    strcat(inputText, (char[]){(char)key, '\0'});
                }
            }
        }

        if (IsKeyPressed(KEY_ENTER) && strlen(inputText) > 0) {
            int inputValue = atoi(inputText);
            if (inputValue >= 0 && inputValue <= 99) {
                printf("Valeur saisie : %d\n", inputValue);

            } else {
                printf("Erreur : La valeur doit être entre 0 et 99 inclus.\n");
            }
            inputText[0] = '\0';
        }

        if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputText) > 0) {
            inputText[strlen(inputText) - 1] = '\0';
        }

        // Gestion de la deuxième boîte de texte
        if (editMode1) {
            int key1 = GetKeyPressed();
            if (key1 > 0) {
                if (isdigit(key1) && strlen(inputText1) < MAX_INPUT_CHARS1) {
                   strcat(inputText1, (char[]){(char)key1, '\0'});
                } else if (key1 == ',') {
                    int inputValue1 = atoi(inputText1);
                    numbers1[numbersCount1++] = inputValue1;
                    cpt1++;
                    if (numbersCount1 >= NUMBERS_COUNT1) {
                        numbersCount1 = 0;
                    }
                    inputText1[0] = '\0';
                }
            }
        }

        if (IsKeyPressed(KEY_ENTER) && strlen(inputText1) > 0) {
            int inputValue1 = atoi(inputText1);
            numbers1[numbersCount1++] = inputValue1;
            cpt1++;

            if (numbersCount1 >= NUMBERS_COUNT1) {
                numbersCount1 = 0;
            }
            inputText1[0] = '\0';
        }

        if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputText1) > 0) {
            inputText1[strlen(inputText1) - 1] = '\0';
        }

        // Ajouter cette section pour créer les rectangles en appuyant sur le bouton Entrer
        if (IsKeyPressed(KEY_ENTER)) {
            for (i = 0; i < cpt1; i++) {
                rectangles[i] = (Rectangle){(i * 70)+400, 350, 70, 70};
            }
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
        DrawText("TRIE PAR COMPTAGE", windowWidth / 2 - 200, 10, 40, BLUE);
        DrawRectangleLinesEx((Rectangle){10, 10, 160, 770}, 4, BLUE);
        DrawRectangleLinesEx((Rectangle){300, 150, 650, 500}, 4, BLUE);

        DrawButtonWithText(buttonBounds1, "Trie", 30, CheckCollisionPointRec(GetMousePosition(), buttonBounds1));
        DrawButtonWithText(buttonBounds2, "Entre", 30, CheckCollisionPointRec(GetMousePosition(), buttonBounds2));
        DrawButtonWithText(buttonBounds3, "Exit", 30, CheckCollisionPointRec(GetMousePosition(), buttonBounds3));

        DrawText("N=", windowWidth / 2 - 240, 710, 30, BLACK);
        DrawRectangleRec(textBox, (mouseOnText && editMode) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE);

<<<<<<< HEAD
        if (strlen(inputText) > 0) {
            int textWidth = MeasureText(inputText, 30);
            DrawText(inputText, (int)textBox.x + (int)(textBox.width - textWidth) / 2, (int)textBox.y + (int)(textBox.height - 30) / 2, 30, BLACK);
        }

        DrawText("T=", windowWidth / 2 - 60, 710, 30, BLACK);
        DrawRectangleRec(textBox1, (mouseOnText1 && editMode1) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)textBox1.x, (int)textBox1.y, (int)textBox1.width, (int)textBox1.height, BLUE);

        if (strlen(inputText1) > 0) {
            int textWidth1 = MeasureText(inputText1, 30);
            DrawText(inputText1, (int)textBox1.x + (int)(textBox1.width - textWidth1) / 2, (int)textBox1.y + (int)(textBox1.height - 30) / 2, 30, BLACK);
        }

        DrawText("Les elements du tableau:", windowWidth / 2 - 170, 170, 30, BLACK);

        for (int i = 0; i < numbersCount1; i++) {
            DrawText(TextFormat("%d", numbers1[i]), windowWidth / 2 - 90 + i * 70, 370, 30, BLACK);
        }

        DrawText(TextFormat("Nombre de saisies: %d", cpt1), windowWidth / 2 - 170, 500, 30, BLACK);

        // Dessiner les rectangles créés en appuyant sur le bouton Entrer
        for (i = 0; i < cpt1; i++) {
            DrawRectangleLinesEx(rectangles[i], 4, BLACK);
        }
=======
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
>>>>>>> 6b58033822ad8ab1cb97c0f282bce6ca4e3b632c

        EndDrawing();
    }

    CloseWindow();

    return 0;
}