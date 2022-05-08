#include "point.h"
#include "raylib.h"

class Piece {
public:
    Piece(Point center = Point{ 0, 0 }, int size = 0): center{center}, size{size} {};
    void render();
    void move(const Point& p) { center = p; }
    void move(const Point& p, int new_size) { center = p; size = new_size; }
    int get_size() { return size; }
    Point get_center() { return center; }

private:
    Point center;
    int size;
};

