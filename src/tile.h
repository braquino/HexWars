#include "point.h"
#include "raylib.h"
#include "utils.h"
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<map>

using namespace std;

class Tile {
public:
    Tile(): Tile(Point{0,0}, 0) {};
    Tile(Point center, int size, HCoords coords = HCoords{0, 0, 0} ) :
            coords{ coords },
            center{ Point{ 0, 0 } },
            size{ size } {
		poly = calculate_poly();
		move(center);
	};
	void render();
    void move(Point new_center);
	vector<Point> get_points() { return poly; }
    map<string, Tile> get_surround();
    Point get_center(){ return center; }
    bool inside_rect(Point rec_start, Point rec_end);
    bool check_collision(Point p);

    HCoords coords;
    bool expanded {false};
    bool selected{false};

private:
	Point center;
	int size;
	vector<Point> poly;

	vector<Point> calculate_poly();
	Point calculate_point(double alpha, double angle);
};

