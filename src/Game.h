#include<string>
#include "raylib.h"
#include "board.h"

using namespace std;

class Game {
public:
	Game(int width, int height, string name) : 
		scr_width{ width }, 
		scr_height{ height },
		head_name{ name } {
		setup();
	};

	void run();

private:
	const int scr_width, scr_height;
	const string head_name;

	void setup();
	void main_loop();
    void mouse_handler(Vector2& last_pos, int& was_down, Board& b);
};

