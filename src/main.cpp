#include "raylib.h"
#include "Game.h"

int main(void)
{
    Game game { 800, 450, "raylib [core] example - basic window" };
    game.run();

    return 0;
}
