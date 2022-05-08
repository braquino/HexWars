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
    Board b{Point{ 0, 0 }, 40, 400, 450, SelectionMode::OnlyLinkedPieces};
    b.fill_retangle();
    Piece p1;
    Piece p2;
    Piece p3;
    b.set_piece(&p1, HCoords{0, 1, -1}.to_str());
    b.set_piece(&p2, HCoords{0, 0, 0}.to_str());
    b.set_piece(&p3, HCoords{3, -2, -1}.to_str());

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
    Point init_pos = Point{min(last_pos.x, curr_pos.x), min(last_pos.y, curr_pos.y)};
    Point final_pos = Point{max(last_pos.x, curr_pos.x), max(last_pos.y, curr_pos.y)};
    Point delta_pos = final_pos - init_pos;

    if (IsMouseButtonDown(0)) {
        if (was_down == 0) {
            last_pos = curr_pos;
        } else if (mouse_down) {
            DrawRectangleLines(init_pos.x_int(), init_pos.y_int(), abs(delta_pos.x_int()), abs(delta_pos.y_int()), GREEN);
        }
        was_down++;
    } else {
        // TODO: Fix it, it doen's consider small taps
        if (was_down > 0 && was_down < 10) {
            b.select(final_pos, shift_ctrl);
        } else if (was_down >= 10){
            b.select(init_pos, final_pos, shift_ctrl);
        }
        was_down = 0;
        last_pos = curr_pos;
    }
}
