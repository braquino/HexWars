#include<cmath>

class Point
{
public:
    Point(double x, double y):x(x),y(y){};

    double x;
    double y;

    int x_int() { return static_cast<int>(round(x)); }
    int y_int() { return static_cast<int>(round(y)); }
    float x_f() { return static_cast<float>(x); }
    float y_f() { return static_cast<float>(y); }

    double distance(const Point& other) {
        Point delta = this->operator-(other);
        return sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    }

    Point& move_to(Point* vector) {
        x = vector->x;
        y = vector->y;
        return *this;
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

    bool operator==(const Point& right) const {
        return x == right.x && y == right.y;
    }
};

