#include "Game.h"

void Game::run() {
    Game::main_loop();
}

void Game::setup() {
	InitWindow(Game::scr_width, Game::scr_height, Game::head_name.c_str());
	SetTargetFPS(60);
}

void Game::main_loop() {

    Tile t{ Point{ 80, 80 }, 20 };

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        t.render();
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
}
