#ifndef POINT_H_
#define POINT_H_

#include<cmath>
#include "raylib.h"

class Point
{
public:
    Point(double x, double y):x(x), y(y){};
    Point(Vector2 v):x(v.x), y(v.y){};

    double x;
    double y;

    int x_int() { return static_cast<int>(round(x)); }
    int y_int() { return static_cast<int>(round(y)); }
    float x_f() { return static_cast<float>(x); }
    float y_f() { return static_cast<float>(y); }
    Vector2 to_vector2() {return Vector2{x_f(), y_f()}; }

    double distance(const Point& other) {
        Point delta = this->operator-(other);
        return sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    }

    bool inside_rec(Point rec_start, Point rec_end) {
        return x >= rec_start.x && y >= rec_start.y &&
                x <= rec_end.x && y <= rec_end.y;
    }

    Point& move_to(Point* vector) {
        x = vector->x;
        y = vector->y;
        return *this;
    }

    static Point point_from_angle(double alpha, double angle) {
        double rad = angle * ( PI / 180 );
        return Point{alpha * cos(rad), alpha * sin(rad)};
    }

    Point operator-(const Point& right) const {
        return Point{ x - right.x, y - right.y };
    }

    Point operator+(const Point& right) const {
        return Point{ x + right.x, y + right.y };
    }

    Point& operator+=(const Point& right) {
        x += right.x;
        y += right.y;
        return *this;
    }

    Point operator/(double right) {
        return Point{x / right, y / right};
    }

    bool operator==(const Point& right) const {
        return x == right.x && y == right.y;
    }
};

#endif
