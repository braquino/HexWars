#include "tile.h"

void Tile::render() {
	DrawPoly(Vector2{ this->center.x_f(), this->center.y_f() },
			 6, (float)this->size, 90, SKYBLUE);
	for (int i = 1; i != this->poly.size() + 1; i++) {
		int idx_f = i - 1;
		int idx_s = i % this->poly.size();
        Color border = this->selected ? GREEN : BLACK;
		DrawLine(this->poly[idx_f].x_int(), this->poly[idx_f].y_int(),
                 this->poly[idx_s].x_int(), this->poly[idx_s].y_int(), border);
	}
}

void Tile::move(Point new_center) {
	Point delta = new_center - this->center;
	this->center = new_center;
	for_each(begin(this->poly), end(this->poly), [&delta](Point& p) { p += delta; });
}

vector<Point> Tile::calculate_poly() {
	vector<Point> left{};
	left.push_back(Point{ (double)this->size, 0 });
	for (double angle : {60, 120, 180, 240, 300})
		left.push_back(this->calculate_point(this->size, angle));
	return left;
}

Point Tile::calculate_point(double alpha, double angle) {
	double rad = angle * ( PI / 180 );
	return Point{alpha * cos(rad), alpha * sin(rad)};
}

map<string, Tile> Tile::get_surround(){
    auto points = this->calculate_poly();
    map<string, Tile> right;
    for (int i = 1; i != this->poly.size() + 1; i++) {
        int idx_f = i - 1;
        int idx_s = i % this->poly.size();
        Point p = points[idx_f] + points[idx_s] + this->center;
        HCoords c = this->coords + SURROUND_COORDS[idx_f];
        right[c.to_str()] = Tile{p, this->size, c};
    }
    return right;
}

bool Tile::inside_rect(Point rec_start, Point rec_end){
    for (Point& p : poly) {
        if (!p.inside_rec(rec_start, rec_end)) return false;
    }
    return true;
}

bool Tile::check_collision(Point p) {
    // TODO: Calculate myself, this workaround is bad
    double k{0.925}; // maximize matching area (circle -> hex)
    return CheckCollisionPointCircle(p.to_vector2(), this->center.to_vector2(), this->size * k);
}
