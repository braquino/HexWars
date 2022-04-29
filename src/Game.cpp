#include "Game.h"

void Game::run() {
    Game::main_loop();
}

void Game::setup() {
	InitWindow(Game::scr_width, Game::scr_height, Game::head_name.c_str());
	SetTargetFPS(60);
}

void Game::main_loop() {

    Vector2 last_mouse_pos = GetMousePosition();
    int mouse_down_frames{false};
    Board b{Point{ 0, 0 }, 40, 400, 450};
    b.fill_retangle();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        b.render();
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        this->mouse_handler(last_mouse_pos, mouse_down_frames, b);

        EndDrawing();
    }

    CloseWindow();
}

void Game::mouse_handler(Vector2& last_pos, int& was_down, Board& b) {
    bool shift_ctrl = (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL) || IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
    bool mouse_down = IsMouseButtonDown(0);
    Vector2 curr_pos = GetMousePosition();
    bool invert = (curr_pos.x < last_pos.x || curr_pos.x < last_pos.x);
    Point last_pos_p = invert ? Point{curr_pos} : Point{last_pos};
    Point curr_pos_p = invert ? Point{last_pos} : Point{curr_pos};
    Point delta_pos = curr_pos_p - last_pos_p;

    if (IsMouseButtonDown(0)) {
        if (was_down == 0) {
            last_pos = curr_pos;
        } else if (mouse_down) {
            DrawRectangleLines(last_pos_p.x_int(), last_pos_p.y_int(), abs(delta_pos.x_int()), abs(delta_pos.y_int()), GREEN);
        }
        was_down++;
    } else {
        if (was_down > 0 && was_down < 10) {
            b.select(curr_pos_p, shift_ctrl);
        } else if (was_down >= 10){
            b.select(last_pos_p, curr_pos_p, shift_ctrl);
        }
        was_down = 0;
        last_pos = curr_pos;
    }
}
