#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include <raygui.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>




int main(){

    const int l = 1000;
    const int h = 800;
Rectangle rec={200,200,100,100};

    InitWindow(l,h,"test");

    while(!WindowShouldClose()){

        ClearBackground(RAYWHITE);

        BeginDrawing();

          DrawRectangle(200,200,200,100,BLUE);
          GuiButton(rec,"click");



        EndDrawing();

    }


    CloseWindow();







return 0 ;}
