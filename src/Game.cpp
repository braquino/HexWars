#include "Game.h"

void Game::run() {
    Game::main_loop();
}

void Game::setup() {
	InitWindow(Game::scr_width, Game::scr_height, Game::head_name.c_str());
	SetTargetFPS(60);
}

void Game::main_loop() {

    Board b{Point{ 0, 0 }, 40, 400, 450};
    b.fill_retangle();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        b.render();
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
}
