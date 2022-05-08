#include "piece.h"
#include <iostream>

void Piece::render() {
    double size_factor{0.5};
    Point v1 = Point::point_from_angle(this->size * size_factor, 90) + this->center;
    Point v2 = Point::point_from_angle(this->size * size_factor, 210) + this->center;
    Point v3 = Point::point_from_angle(this->size * size_factor, 330) + this->center;
    DrawTriangle(v3.to_vector2(), v2.to_vector2(), v1.to_vector2(), BLACK);
}
