#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INPUT_CHARS1 2
#define NUMBERS_COUNT1 8

typedef struct {
    int *t;
    int n;
} vecteur;

void DrawButtonWithText(Rectangle bounds, const char *text, int fontSize, bool isMouseOnButton) {
    DrawRectangleRec(bounds, isMouseOnButton ? DARKGRAY : LIGHTGRAY);
    DrawRectangleLinesEx((Rectangle){bounds.x, bounds.y, bounds.width, bounds.height}, 2, BLUE);

    // Calculer la position du texte pour le centrer dans le bouton
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 2);
    Vector2 textPosition = {bounds.x + bounds.width / 2 - textSize.x / 2, bounds.y + bounds.height / 2 - textSize.y / 2};

    DrawTextEx(GetFontDefault(), text, textPosition, fontSize, 2, BLUE);
}

vecteur trie(vecteur v) {
    int max = v.t[0];
    vecteur m, r;
    int i, j;

    // Trouver la valeur maximale dans le vecteur
    for (i = 1; i < v.n; i++) {
        if (v.t[i] > max) {
            max = v.t[i];
        }
    }

    // Allocation dynamique du vecteur m.t
    m.t = (int *)calloc(max + 1, sizeof(int));  // Utilisation de calloc pour initialiser à zéro

    // Compter les occurrences de chaque valeur dans le vecteur v.t
    for (i = 0; i < v.n; i++) {
        m.t[v.t[i]]++;
    }

    // Allocation dynamique du vecteur r.t
    r.t = (int *)malloc(v.n * sizeof(int));

    // Remplir le vecteur trié r.t en utilisant le tri par comptage
    int k = 0;
    for (i = 0; i <= max; i++) {
        for (j = 0; j < m.t[i]; j++) {
            r.t[k++] = i;
        }
    }

    // Libérer la mémoire allouée pour le vecteur m.t
    free(m.t);

    // Ajuster la taille de r
    r.n = v.n;

    return r;
}

// la fonction qui affiche le vecteur
void affich(vecteur v) {
    int i;
    printf("Affichage du vecteur trié : \n");

    for (i = 0; i < v.n; i++) {
        printf("v.t[%d] = %d\n", i, v.t[i]);
    }
}

int main(void) {
    const int windowWidth = 1000;
    const int windowHeight = 800;

    InitWindow(windowWidth, windowHeight, "projet tp c");

    Rectangle buttonBounds1 = {30, 50, 120, 50};
    Rectangle buttonBounds2 = {30, 130, 120, 50};
    Rectangle buttonBounds3 = {30, 700, 120, 50};

    Rectangle rectangles[10];
    Rectangle rectangles2[10];
    Rectangle textBox = {windowWidth / 2 - 200, 700, 100, 50};
    bool mouseOnText = false;
    bool editMode = false;
    char inputText[3] = "\0"; // Pour un entier décimal
    int i,j;

    vecteur v, y;

    Rectangle textBox1 = {windowWidth / 2 - 10, 700, 400, 50};
    bool mouseOnText1 = false;
    bool editMode1 = false;
    bool trv=false;
    char inputText1[MAX_INPUT_CHARS1 + 1] = "\0"; // +1 for the null terminator

    int numbers1[NUMBERS_COUNT1];  // Tableau pour stocker les nombres saisis
    int numbersCount1 = 0;
    int cpt1 = 0; // Variable pour compter le nombre de saisies


    SetExitKey(KEY_NULL);       // Disable KEY_ESCAPE to close window, X-button still works

    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit

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
            if (inputValue >= 0 && inputValue <= 1) {
                printf("Valeur saisie : %d\n", inputValue);

            } else {
                printf("Erreur : La valeur doit être entre 0 et 99 inclus.\n");
            }
            inputText[0] = '\0';
        }

        if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputText) > 0) {
            inputText[strlen(inputText) - 1] = '\0';
        }

        // Gestionde la deuxième boîte de texte
        if (editMode1) {
            int key1 = GetKeyPressed();
            if (key1 > 0) {
                if (isdigit(key1) && strlen(inputText1) < MAX_INPUT_CHARS1) {
                   strcat(inputText1, (char[]){(char)key1, '\0'});

                } else if (key1 == ',') {
                    int inputValue1 = atoi(inputText1);
                    numbers1[numbersCount1++] = inputValue1;
                    v.t[i]= inputValue1;
                    cpt1++;

                }
            }
        v.t=(int*)malloc(sizeof(int)*cpt1);
        for(i=0;i<v.n;i++){

            v.t[i]=numbers1[i];
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
        v.n=cpt1;

        if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputText1) > 0) {
            inputText1[strlen(inputText1) - 1] = '\0';
        }

        // Ajouter cette section pour créer les rectangles en appuyant sur le bouton Entrer
        if (IsKeyPressed(KEY_ENTER)) {
            for (i = 0; i < cpt1; i++) {
                rectangles[i] = (Rectangle){(i * 70)+400, 350, 70, 70};
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buttonBounds2)) {
            for (j = 0; j < cpt1; j++) {
                rectangles2[j] = (Rectangle){(j * 70)+400, 450, 70, 70};
                trv=true;
            }
        }

        // Gestion du bouton Entre
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buttonBounds1)) {
            y = trie(v);
            affich(y);

            // Libérer la mémoire allouée pour les vecteurs v.t et y.t

            printf("Bouton Entre appuyé!\n");
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buttonBounds3)) {

        // Update
        //----------------------------------------------------------------------------------
        // Detect if X-button or KEY_ESCAPE have been pressed to close window
        exitWindowRequested = true;}

        if (exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation

            if (IsKeyPressed(KEY_Y))     CloseWindow();

            else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }

        BeginDrawing();
        DrawText("TRIE PAR COMPTAGE", windowWidth / 2 - 200, 10, 40, BLUE);
        DrawRectangleLinesEx((Rectangle){10, 10, 160, 770}, 4, BLUE);
        DrawRectangleLinesEx((Rectangle){300, 150, 650, 500}, 4, BLUE);

        DrawButtonWithText(buttonBounds1, "Trier", 30, CheckCollisionPointRec(GetMousePosition(), buttonBounds1));
        DrawButtonWithText(buttonBounds2, "Afficher", 30, CheckCollisionPointRec(GetMousePosition(), buttonBounds2));
        DrawButtonWithText(buttonBounds3, "Exit", 30, CheckCollisionPointRec(GetMousePosition(), buttonBounds3));

        DrawText("N=", windowWidth / 2 - 240, 710, 30, BLACK);
        DrawRectangleRec(textBox, (mouseOnText && editMode) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE);

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

        DrawText(TextFormat("Nombre de saisies: %d", cpt1), windowWidth / 2 - 170, 600, 30, BLACK);

        // Dessiner les rectangles créés en appuyant sur le bouton Entrer
        for (i = 0; i < cpt1; i++) {
            DrawRectangleLinesEx(rectangles[i], 4, BLACK);
        }

if(trv){
        for (j = 0; j< cpt1; j++) {
            DrawRectangleLinesEx(rectangles2[j], 4, BLACK);

        }
        for ( j = 0; j < cpt1; j++) {
            DrawText(TextFormat("%d", y.t[j]), windowWidth / 2 - 90 + j * 70, 470, 30, BLACK);
        }

}

if (exitWindowRequested)
            {
                DrawRectangle(0, 200, windowWidth, 200, BLACK);
                DrawText("Are you sure you want to exit program? [Y/N]", 40, 280, 30, WHITE);
            }
            //else DrawText("Try to close the window to get confirmation message!", 120, 200, 20, LIGHTGRAY);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
